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

/*
constexpr GPIO_Type * convertAddressToPtr (uint32_t inputAddress)
{
	constexpr uint32_t adds[] = GPIO_BASE_ADDRS;
	constexpr GPIO_Type * ptrs[] = GPIO_BASE_PTRS;
	uint32_t i = 0;

	for (auto& gpio : adds)
	{
		if (gpio == inputAddress)
		{
			return ptrs[i];
		}
		i++;
	}
	return nullptr;
}
*/

template <uint32_t baseAddress, uint32_t pin>
class GPIOPin {
public:
	static void set() { GPIO_WritePinOutput(reinterpret_cast<GPIO_Type*>(baseAddress), pin, 1); }
	static void clr() { GPIO_WritePinOutput(reinterpret_cast<GPIO_Type*>(baseAddress), pin, 0); }
	static bool read() { return GPIO_PinRead(reinterpret_cast<GPIO_Type*>(baseAddress), pin); }
};

} /* namespace Driver */

#endif /* DRIVERS_GPIOPIN_H_ */
