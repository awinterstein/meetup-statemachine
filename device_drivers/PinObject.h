/*
 * Pin.h
 *
 *  Created on: 28 Oct 2018
 *      Author: meetup
 */

#ifndef DRIVERS_PIN_H_
#define DRIVERS_PIN_H_

#include <fsl_gpio.h>

namespace Driver {

#define CONCAT_NOEXP(x, y)	x##y
#define CONCAT_EXP(x, y)	CONCAT_NOEXP(x, y)

struct pinInfo {
	PORT_Type* port_;
	GPIO_Type* gpio_;
	uint32_t   pin_;
};

#define DECLARE_PIN_AS(Pinname, TypeName)	constexpr Driver::pinInfo CONCAT_EXP(pin, __LINE__) { Pinname##_PORT, Pinname##_GPIO, Pinname##_PIN}; using TypeName = Driver::PinObject<CONCAT_EXP(pin, __LINE__)>;

template <const pinInfo& pinInformation>
class PinObject {
public:
	static void set() { GPIO_WritePinOutput(pinInformation.gpio_, pinInformation.pin_, 1); }
	static void clr() { GPIO_WritePinOutput(pinInformation.gpio_, pinInformation.pin_, 0); }
	static bool read() { return GPIO_PinRead(pinInformation.gpio_, pinInformation.pin_); }
};

} /* namespace Driver */

#endif /* DRIVERS_PIN_H_ */
