#include "setup.hpp"

#include "builtins_statemachine.hpp"
#include "support_statemachine.hpp"

#include "generated_state_machine_blinky.hpp"

units::micros currentTimeMicros()
{
  const auto now = HAL::MonoClock::microseconds();
  return now.count();
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
  
  finish();
  return 0;
}
