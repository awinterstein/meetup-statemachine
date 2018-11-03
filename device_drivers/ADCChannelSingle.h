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

namespace Driver {

struct channelInfo {
	ADC_Type* adc_;
	adc16_channel_config_t* chan_;
	uint32_t chanGroup_;
};

#define DECLARE_ADC_CHANNEL_AS(ADCName, ADCChannelIndex, TypeName)	constexpr Driver::channelInfo CONCAT_EXP(adcChannel, __LINE__) { ADCName##_PERIPHERAL, ADCName##_channelsConfig[ADCChannelIndex], 0u }; using TypeName = Driver::channelInfo<CONCAT_EXP(adcChannel, __LINE__)>;

template <const channelInfo&  chanInfo>
class ADCChannelSingle
{
	static uint32_t getRawValue ()
	{
        ADC16_SetChannelConfig(chanInfo.adc_, chanInfo.chanGroup_, chanInfo.chan_);
        while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(chanInfo.adc_, chanInfo.chanGroup_))) { }
        return ADC16_GetChannelConversionValue(chanInfo.adc_, chanInfo.chanGroup_);
	}
};

} /* namespace Driver */

#endif /* DRIVERS_BUTTONOVERADC_H_ */
