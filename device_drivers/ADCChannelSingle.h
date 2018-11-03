/*
 * Pin.h
 *
 *  Created on: 03 Nov 2018
 *      Author: meetup
 */

#ifndef DRIVERS_BUTTONOVERADC_H_
#define DRIVERS_BUTTONOVERADC_H_

#include <fsl_adc16.h>

namespace Driver {

template <ADC_Type * usedADC>
class ADCChannelSingle
{
	static uint32_t getRawValue ()
	{
        ADC16_SetChannelConfig(usedADC, 0u, &adc16ChannelConfigStruct);
        while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(usedADC, 0u))) { }
        return ADC16_GetChannelConversionValue(usedADC, 0u);
	}
};

} /* namespace Driver */

#endif /* DRIVERS_BUTTONOVERADC_H_ */
