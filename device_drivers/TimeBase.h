/*
 * TimeBase.h
 *
 *  Created on: 10 Nov 2018
 *      Author: vagrant
 */

#ifndef DRIVERS_TIMEBASE_H_
#define DRIVERS_TIMEBASE_H_

#include <chrono>
#include <fsl_pit.h>

namespace Driver {

template <uint32_t pitBase, clock_name_t clockSource>
class TimeBase {
public:
	static std::chrono::milliseconds milliseconds() const
	{
		const auto clockFrequency = CLOCK_GetFreq(clockSource);
		const auto instance = reinterpret_cast<PIT_Type*>(pitBase);
		const auto lifetimeCount = std::numeric_limits<uint64_t>::max() - PIT_GetLifetimeTimerCount(instance);

		return std::chrono::milliseconds{COUNT_TO_MSEC(lifetimeCount, clockFrequency)};
	}
};

} /* namespace Driver */

#endif /* DRIVERS_TIMEBASE_H_ */
