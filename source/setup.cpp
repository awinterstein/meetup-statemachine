#include "setup.hpp"


void setup()
{
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
	BOARD_InitDebugConsole();

	HAL::DISPLAY::init();
}



void finish ()
{
  /* Force the counter to be placed into memory. */
  volatile static int i = 0;

  /* Enter an infinite loop, just incrementing a counter. */
  while (1)
    {
      i++;
    }
}
