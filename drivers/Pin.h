/*
 * Pin.h
 *
 *  Created on: 28 Oct 2018
 *      Author: meetup
 */

#ifndef DRIVERS_PIN_H_
#define DRIVERS_PIN_H_

#include <fsl_gpio.h>

namespace DRVR {

constexpr GPIO_Type* cnvAddrToPointer(uint32_t addr)
{
	switch (addr)
	{
		case GPIOA_BASE: return GPIOA;
		case GPIOB_BASE: return GPIOB;
		case GPIOC_BASE: return GPIOC;
		case GPIOD_BASE: return GPIOD;
		default: return GPIOE;
	}
}

template <uintptr_t gpioBase_, uint32_t pin_>
class Pin {
public:
	Pin();
	virtual ~Pin();

	static void set() { GPIO_WritePinOutput(cnvAddrToPointer(gpioBase_), pin_, 1); }
	static void clr() { GPIO_WritePinOutput(cnvAddrToPointer(gpioBase_), pin_, 0); }
	static bool read() { return GPIO_PinRead(cnvAddrToPointer(gpioBase_), pin_); }
};

} /* namespace DRVR */

#endif /* DRIVERS_PIN_H_ */
