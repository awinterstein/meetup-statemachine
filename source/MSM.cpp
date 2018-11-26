#include "setup.hpp"
#include <boost/msm/back/state_machine.hpp>

// back-end
#include <boost/msm/back/state_machine.hpp>
//front-end
#include <boost/msm/front/state_machine_def.hpp>

using namespace std;
namespace msm = boost::msm;
namespace mpl = boost::mpl;

// events
struct StartEv
{
};
struct HeartBeatEv
{
};
struct LeftButtonEv
{
};
struct RightButtonEv
{
};

// front-end: define the FSM structure
struct Blinky: public msm::front::state_machine_def<Blinky>
{
	template<class Event, class FSM>
	void on_entry(Event const&, FSM&)
	{
		HAL::DISPLAY::writeTopLine("entering: Blinky");
	}
	template<class Event, class FSM>
	void on_exit(Event const&, FSM&)
	{
		HAL::DISPLAY::writeTopLine("leaving: Blinky");
	}

	// The list of FSM states
	struct Start: public msm::front::state<>
	{
		// every (optional) entry/exit methods get the event passed.
		template<class Event, class FSM>
		void on_entry(Event const&, FSM&)
		{
			HAL::DISPLAY::writeBottomLine("Start");
		}
		template<class Event, class FSM>
		void on_exit(Event const&, FSM&)
		{
			HAL::DISPLAY::writeTopLine("leaving: Start");
		}
	};
	struct Blink1: public msm::front::state<>
	{
		template<class Event, class FSM>
		void on_entry(Event const&, FSM&)
		{
			HAL::DISPLAY::writeBottomLine("Blink1");
		}
		template<class Event, class FSM>
		void on_exit(Event const&, FSM&)
		{
			HAL::DISPLAY::writeTopLine("leaving: Blink1");
		}
	};

	struct Blink2: public msm::front::state<>
	{
		template<class Event, class FSM>
		void on_entry(Event const&, FSM&)
		{
			HAL::DISPLAY::writeBottomLine("Blink2");
		}
		template<class Event, class FSM>
		void on_exit(Event const&, FSM&)
		{
			HAL::DISPLAY::writeTopLine("leaving: Blink2");
		}
	};

	// the initial state of the player SM. Must be defined
	typedef Start initial_state;

	// transition actions
	void start(const StartEv&)
	{
		HAL::DISPLAY::writeTopLine("starting\n");
	}
	void left_button_pressed(const LeftButtonEv &)
	{
	}
	void right_button_pressed(const RightButtonEv &)
	{
	}
	void heartbeat(const HeartBeatEv &)
	{
	}

	typedef Blinky p; // makes transition table cleaner

	// Transition table for player
	struct transition_table: mpl::vector<
			//    Start     Event         Next      Action				 Guard
			//  +---------+-------------+---------+---------------------+----------------------+
			a_row<Start, StartEv, Blink1, &p::start>,

			a_row<Blink1, LeftButtonEv, Blink2, &p::left_button_pressed>,
			a_row<Blink1, HeartBeatEv, Blink1, &p::heartbeat>,

			a_row<Blink2, RightButtonEv, Blink1, &p::right_button_pressed>,
			a_row<Blink2, HeartBeatEv, Blink2, &p::heartbeat> >
	{
	};

	// Replaces the default no-transition response.
	template<class FSM, class Event>
	void no_transition(Event const& e, FSM&, int state)
	{
		HAL::DISPLAY::writeTopLine("no tr. in state %d on event %s",
				state, typeid(e).name());
		printf("no tr. in state %d on event %s",
				state, typeid(e).name());
	}
};

// Pick a back-end
typedef msm::back::state_machine<Blinky> CompleteBlinky;


void statemachine_main()
{
	CompleteBlinky p;
	// needed to start the highest-level SM. This will call on_entry and mark the start of the SM
	p.start();

	auto delay = 2000ms;
	auto nextHeartBeat = HAL::MonoClock::microseconds() + delay;

	p.process_event(StartEv());

	while (true)
	{
		if (HAL::EVENT_BUTTON_LEFT::shouldTriggerEvent())
		{
			p.process_event(LeftButtonEv());
		}
		else if (HAL::EVENT_BUTTON_RIGHT::shouldTriggerEvent())
		{
			p.process_event(RightButtonEv());
		}

		if (nextHeartBeat < HAL::MonoClock::microseconds())
		{
			nextHeartBeat = HAL::MonoClock::microseconds() + delay;
			p.process_event(HeartBeatEv());
		}
	}
}

int main()
{
	setup();
	statemachine_main();
	finish();
	return 0;
}
