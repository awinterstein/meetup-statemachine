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

struct channelInfo {
	ADC_Type* adc_;
	adc16_channel_config_t* chan_;
	uint32_t chanGroup_;
};

#define DECLARE_ADC_CHANNEL_AS(ADCName, ADCChannelIndex, TypeName) constexpr Driver::channelInfo CONCAT_EXP(ADCName, TypeName) { ADCName##_PERIPHERAL, &ADCName##_channelsConfig[ADCChannelIndex], 0u }; using TypeName = Driver::ADCChannelSingle<CONCAT_EXP(ADCName, TypeName), 3300, 12>;

template <const channelInfo&  chanInfo, int32_t referenceVoltage, int32_t bits>
class ADCChannelSingle
{
public:
	static int32_t getADCCount ()
	{
        ADC16_SetChannelConfig(chanInfo.adc_, chanInfo.chanGroup_, chanInfo.chan_);
        while ( ! (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(chanInfo.adc_, chanInfo.chanGroup_))) { }
        return ADC16_GetChannelConversionValue(chanInfo.adc_, chanInfo.chanGroup_);
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
