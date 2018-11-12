/*
 * GPIOPin.h
 *
 *  Created on: 28 Oct 2018
 *      Author: meetup
 */

#ifndef DRIVERS_GPIOPIN_H_
#define DRIVERS_GPIOPIN_H_

#include <fsl_gpio.h>
#include <macro_utilities.h>

namespace Driver {

namespace
{
	inline static bool isOutputSetToHigh(GPIO_Type *base, uint32_t pin)
	{
		return (((base->PDOR) >> pin) & 0x01U);
	}

	inline static bool isConfiguredForOutput(GPIO_Type *base, uint32_t pin)
	{
		return (((base->PDDR) >> pin) & 0x01U);
	}
}

template <uint32_t baseAddress, uint32_t pin>
class GPIOPin {
public:
	static void set() { GPIO_WritePinOutput(reinterpret_cast<GPIO_Type*>(baseAddress), pin, 1); }
	static void clr() { GPIO_WritePinOutput(reinterpret_cast<GPIO_Type*>(baseAddress), pin, 0); }
	static bool read()
	{
		if (isConfiguredForOutput(reinterpret_cast<GPIO_Type*>(baseAddress), pin))
		{
			return isOutputSetToHigh(reinterpret_cast<GPIO_Type*>(baseAddress), pin);
		}
		else
		{
			return GPIO_PinRead(reinterpret_cast<GPIO_Type*>(baseAddress), pin);
		}
	}
};

} /* namespace Driver */

#endif /* DRIVERS_GPIOPIN_H_ */
