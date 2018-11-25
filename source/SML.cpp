/**
 *
 * Find reference material here:
 *
 * 		http://boost-experimental.github.io/sml/examples/index.html#hello-world
 *
 */


#include "setup.hpp"

#include <boost/sml.hpp>

namespace sml = boost::sml;
using namespace std::chrono_literals;


struct Event_Start {};
struct EvButtonLeft {};
struct EvButtonRight {};
struct EvHeartBeat {};

namespace Blink1
{
	int tocks = 0;
	auto EntryAction = [] 		{ HAL::DISPLAY::writeBottomLine("Blink1"); tocks = 0; };
	auto ExitAction = []  		{ HAL::DISPLAY::writeBottomLine("~Blink1"); };
	auto LeftButtonAction = [] 	{ printf("Blink1 - Left Button\n"); };
	auto HeartBeatAction = [] 	{ HAL::DISPLAY::writeTopLine("tock: %d\n", tocks); tocks++; };
}

namespace Blink2
{
    int ticks = 0;
	auto EntryAction = []		{ HAL::DISPLAY::writeBottomLine("Blink2"); ticks = 0; };
	auto ExitAction = []        { HAL::DISPLAY::writeBottomLine("~Blink2"); };
	auto RightButtonAction = [] { printf("Blink2 - Right Button\n");  };
	auto HeartBeatAction = []   { HAL::DISPLAY::writeTopLine("tick: %d", ticks); ticks++; };
}

struct Blinky
{
  auto operator()() const
  {
    using namespace sml;
    return make_transition_table(
      *"start"_s   + event<Event_Start>   = "blink 1"_s,

      "blink 1"_s + sml::on_entry<_>     / Blink1::EntryAction,
      "blink 1"_s + sml::on_exit<_>      / Blink1::ExitAction,
      "blink 1"_s + event<EvButtonLeft>  / Blink1::LeftButtonAction = "blink 2"_s,
      "blink 1"_s + event<EvHeartBeat>   / Blink1::HeartBeatAction,

	  "blink 2"_s + sml::on_entry<_>     / Blink2::EntryAction,
	  "blink 2"_s + sml::on_exit<_>      / Blink2::ExitAction,
      "blink 2"_s + event<EvButtonRight> / Blink2::RightButtonAction = "blink 1"_s,
      "blink 2"_s + event<EvHeartBeat>   / Blink2::HeartBeatAction
    );
  }
};

void statemachine_main()
{
	using namespace sml;

	sm<Blinky> blinky;

	auto delay = 500ms;
	auto nextHeartBeat = HAL::MonoClock::microseconds() + delay;

	blinky.process_event(Event_Start{});

	while (true)
	{
		if (HAL::BUTTON_LEFT::isPressed())
		{
			blinky.process_event(EvButtonLeft());
		}
		else if (HAL::BUTTON_RIGHT::isPressed())
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
