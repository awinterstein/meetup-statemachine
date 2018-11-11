/*
 * MonotonicClock.h
 *
 *  Created on: 10 Nov 2018
 *      Author: vagrant
 */

#ifndef DRIVERS_MONOTONICCLOCK_H_
#define DRIVERS_MONOTONICCLOCK_H_

#include <chrono>
#include <fsl_pit.h>

namespace Driver {

using namespace std::chrono_literals;

template <uint32_t pitBase, clock_name_t clockSource>
class MonotonicClock {
public:
	static std::chrono::milliseconds milliseconds()
	{
		const auto clockFrequency = CLOCK_GetFreq(clockSource);
		const auto instance = reinterpret_cast<PIT_Type*>(pitBase);
		const auto lifetimeCount = std::numeric_limits<uint64_t>::max() - PIT_GetLifetimeTimerCount(instance);

		return std::chrono::milliseconds{COUNT_TO_MSEC(lifetimeCount, clockFrequency)};
	}

	static void delay (std::chrono::milliseconds msToBusyWait)
	{
		const auto start = milliseconds();
		while (milliseconds() - start < msToBusyWait) {};
	}
};

} /* namespace Driver */

#endif /* DRIVERS_MONOTONICCLOCK_H_ */
