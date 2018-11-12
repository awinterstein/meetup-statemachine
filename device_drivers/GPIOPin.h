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

struct pinInfo {
	PORT_Type* port_;
	GPIO_Type* gpio_;
	uint32_t   pin_;
};

#define DECLARE_PIN_AS(Pinname, TypeName)	constexpr Driver::pinInfo CONCAT_EXP(Pinname, TypeName) { Pinname##_PORT, Pinname##_GPIO, Pinname##_PIN}; using TypeName = Driver::GPIOPin<CONCAT_EXP(Pinname, TypeName)>;

template <const pinInfo& pinInformation>
class GPIOPin {
public:
	static void set() { GPIO_WritePinOutput(pinInformation.gpio_, pinInformation.pin_, 1); }
	static void clr() { GPIO_WritePinOutput(pinInformation.gpio_, pinInformation.pin_, 0); }
	static bool read() { return GPIO_PinRead(pinInformation.gpio_, pinInformation.pin_); }
};

} /* namespace Driver */

#endif /* DRIVERS_GPIOPIN_H_ */
