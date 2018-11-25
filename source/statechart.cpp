/**
 *
 * Find reference material here:
 *
 * 		https://www.boost.org/doc/libs/1_53_0/libs/statechart/doc/index.html
 *
 */


#include "setup.hpp"

#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/mpl/list.hpp>

using namespace std::chrono_literals;

namespace mpl = boost::mpl;
namespace sc = boost::statechart;

struct EvStart: sc::event<EvStart>
{
};
struct EvButtonLeft: sc::event<EvButtonLeft>
{
};
struct EvButtonRight: sc::event<EvButtonRight>
{
};
struct EvHeartBeat: sc::event<EvHeartBeat>
{
};

struct Active;
struct Blinky: sc::state_machine<Blinky, Active>
{
};

struct Blink1;
struct Blink2;

// The simple_state class template accepts up to four parameters:
// - The third parameter specifies the inner initial state, if
//   there is one. Here, only Active has inner states, which is
//   why it needs to pass its inner initial state Blink2 to its
//   base
// - The fourth parameter specifies whether and what kind of
//   history is kept

// Active is the outermost state and therefore needs to pass the
// state machine class it belongs to
struct Active: sc::simple_state<Active, Blinky, Blink1>
{
	typedef sc::transition<EvStart, Active> reactions;

public:
	Active()
	{
		HAL::DISPLAY::writeBottomLine("Active");
	}

	void blib(const EvHeartBeat &)
	{
		printf("active-HB\n");
	}

	~Active()
	{
		HAL::DISPLAY::writeBottomLine("~Active");
	}
};

// Blink2 and Blink1 both specify Active as their Context,
// which makes them nested inside Active
struct Blink1: sc::simple_state<Blink1, Active>
{
	typedef mpl::list<
				sc::transition<EvButtonRight, Blink2>,
				sc::transition<EvHeartBeat, Blink1, Active, &Active::blib>
			> reactions;

	Blink1()
	{
		HAL::DISPLAY::writeBottomLine("Blink1");
		printf("blink1\n");
	}

	~Blink1()
	{
		printf("~blink1\n");
		HAL::DISPLAY::writeBottomLine("~Blink1");
	}
};

struct Blink2: sc::simple_state<Blink2, Active>
{
	typedef mpl::list<
			sc::transition<EvButtonLeft, Blink1>,
			sc::transition<EvHeartBeat, Blink2, Active, &Active::blib>
			> reactions;

	Blink2()
	{
		printf("blink2\n");

		HAL::DISPLAY::writeBottomLine("Blink2");
	}

	~Blink2()
	{
		printf("~blink2\n");

		HAL::DISPLAY::writeBottomLine("~Blink2");
	}
};

// Because the context of a state must be a complete type (i.e.
// not forward declared), a machine must be defined from
// "outside to inside". That is, we always start with the state
// machine, followed by outermost states, followed by the direct
// inner states of outermost states and so on. We can do so in a
// breadth-first or depth-first way or employ a mixture of the
// two.

void statemachine_main()
{
	Blinky blinky;
	blinky.initiate();
	blinky.process_event(EvStart());

	auto delay = 500ms;
	auto nextHeartBeat = HAL::MonoClock::microseconds() + delay;

	while (true)
	{
		if (HAL::simpleLeftButton.isPressed())
		{
			blinky.process_event(EvButtonLeft());
		}
		else if (HAL::simpleRightButton.isPressed())
		{
			blinky.process_event(EvButtonRight());
		}

		if (nextHeartBeat < HAL::MonoClock::microseconds())
		{
			nextHeartBeat = HAL::MonoClock::microseconds() + delay;
			blinky.process_event(EvHeartBeat());
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
