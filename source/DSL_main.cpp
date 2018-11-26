/**
 *
 * Find reference material here:
 *
 * 		https://github.com/rsveldema/state_machine_DSL
 *
 */

#include "setup.hpp"

#include "builtins_statemachine.hpp"
#include "support_statemachine.hpp"

#include "generated_state_machine_blinky.hpp"

std::chrono::microseconds currentTimeMicros()
{
	return HAL::MonoClock::microseconds();
}

static void* tmp = 0;

void set_thread_local_state_machine_ptr(void*p)
{
	tmp = p;
}

void *get_thread_local_state_machine_ptr()
{
	return tmp;
}

#include "../DSL/generated_state_machine_blinky.cpp"

int main()
{
	setup();

	blinky::Blinky stateMachine;
	stateMachine.initial_transition(stateMachine.state_union.bootup);

	while (true)
	{
		if (HAL::EVENT_BUTTON_LEFT::shouldTriggerEvent())
		{
			stateMachine.emit(stateMachine.b1);
		}
		if (HAL::EVENT_BUTTON_RIGHT::shouldTriggerEvent())
		{
			stateMachine.emit(stateMachine.b2);
		}
		stateMachine.process_delayed_events();
	}

	finish();
	return 0;
}
