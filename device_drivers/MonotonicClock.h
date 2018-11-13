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
		const auto instance = reinterpret_cast<PIT_Type*>(pitBase);
		return convertLifeTimeToTime(PIT_GetLifetimeTimerCount(instance));
	}

	static void delay (std::chrono::milliseconds msToBusyWait)
	{
		const auto start = milliseconds();
		while (milliseconds() - start < msToBusyWait) {};
	}
private:
	static std::chrono::milliseconds convertLifeTimeToTime (uint64_t liveTimeCount)
	{
		const auto clockFrequency	= CLOCK_GetFreq(clockSource);
		const auto sec				= std::chrono::seconds{TIMEBASE_1_TICKS - uint32_t(liveTimeCount >> 32U)};
		const auto lowCount			= TIMEBASE_0_TICKS - uint32_t(0xFFFFFFFF & liveTimeCount);
		const auto msec				= std::chrono::milliseconds{COUNT_TO_MSEC(lowCount, clockFrequency)};
		return sec + msec;
	}
};

} /* namespace Driver */

#endif /* DRIVERS_MONOTONICCLOCK_H_ */
