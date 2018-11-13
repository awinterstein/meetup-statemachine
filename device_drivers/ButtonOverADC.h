/*
 * Pin.h
 *
 *  Created on: 03 Nov 2018
 *      Author: meetup
 */

#ifndef DRIVERS_ADCCHANNELSINGLE_H_
#define DRIVERS_ADCCHANNELSINGLE_H_

#include <ADCChannelSingle.h>

namespace Driver {

template <typename adc, int32_t targetVoltage, int32_t voltageTollerance>
class ButtonOverADC {
public:
	ButtonOverADC();
	virtual ~ButtonOverADC();

	static bool isPressed ()
	{
		const auto inputVoltage = adc::getVoltage();
		return lowerBound_ <= inputVoltage && inputVoltage <= upperBound_;
	}

private:
	static constexpr auto lowerBound_ = float(targetVoltage - voltageTollerance) / 1000.0f;
	static constexpr auto upperBound_ = float(targetVoltage + voltageTollerance) / 1000.0f;
};


} /* namespace Driver */

#endif /* DRIVERS_ADCCHANNELSINGLE_H_ */
