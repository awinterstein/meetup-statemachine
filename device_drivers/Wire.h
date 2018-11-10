/*
 * Wire.h
 *
 *  Created on: 10 Nov 2018
 *      Author: vagrant
 */

#ifndef DRIVERS_WIRE_H_
#define DRIVERS_WIRE_H_

#include <GPIOPin.h>

namespace Driver {

namespace {
	#warning "Replace by something that makes more sense"
	static void delayMicroSec (uint32_t uSec)
	{
		for (uint64_t volatile i = uSec; i ; i--) {}
	}
}

template <typename sourcePin, typename sinkPin>
class Wire {
public:
	static bool isCutted()
	{
		invertPins();
		delayMicroSec(10);
		return sourcePin != sinkPin;
	}

private:
	static void invertPins()
	{
		if (sinkPin::read())
		{
			sourcePin::clr();
		}
		else
		{
			sourcePin::set();
		}
	}
};

} /* namespace Driver */

#endif /* DRIVERS_WIRE_H_ */
