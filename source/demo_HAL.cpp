#include "setup.hpp"

int main(void)
{
  setup();
  
	while (1)
	{
		const auto startTime = HAL::MonoClock::microseconds();

		HAL::DISPLAY::writeTopLine("Button adc %d", int32_t(HAL::COMMON_ADC::getVoltage() * 1000));
		HAL::DISPLAY::writeBottomLine("Pressed: %s", HAL::BUTTON_SELECT::isPressed()	? "SEL"		:
				 	 	 	 	 	 	 	 	 	 HAL::BUTTON_LEFT::isPressed()		? "LEFT" 	:
													 HAL::BUTTON_DOWN::isPressed()		? "DOWN" 	:
													 HAL::BUTTON_UP::isPressed()		? "UP" 		:
													 HAL::BUTTON_RIGHT::isPressed()		? "RIGHT" 	: "NONE");
	}

    return 0;
}
