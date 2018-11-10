/*
 * Pin.h
 *
 *  Created on: 03 Nov 2018
 *      Author: meetup
 */

#ifndef DRIVERS_BUTTONOVERADC_H_
#define DRIVERS_BUTTONOVERADC_H_

#include <fsl_adc16.h>
#include <macro_utilities.h>
#include <math.h>

namespace Driver {

template <uint32_t adcBaseAddr, adc16_channel_config_t* channelSetting, int32_t referenceVoltage, int32_t bits>
class ADCChannelSingle
{
public:
	static int32_t getADCCount ()
	{
		const auto adcBasePtr = reinterpret_cast<ADC_Type*>(adcBaseAddr);
		const auto channelGrp = 0lu;

        ADC16_SetChannelConfig(adcBasePtr, channelGrp, channelSetting);

        while ( ! (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(adcBasePtr, channelGrp))) { }

        return ADC16_GetChannelConversionValue(adcBasePtr, channelGrp);
	}

	static float getVoltage ()
	{
		const auto rawADC = getADCCount();
		const auto maxCount = pow(int32_t(2), bits) -1;
		const float refVoltage  = float(referenceVoltage) / 1000;
		return refVoltage * rawADC / maxCount;
	}
};

} /* namespace Driver */

#endif /* DRIVERS_BUTTONOVERADC_H_ */
