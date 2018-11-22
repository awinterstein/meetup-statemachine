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

template <uint32_t pitBase, clock_name_t clockSource, uint32_t secondsDowncountingMax, typename msGetter>
class MonotonicClock {
public:

#if defined(FSL_FEATURE_PIT_HAS_LIFETIME_TIMER) && FSL_FEATURE_PIT_HAS_LIFETIME_TIMER

	static std::chrono::microseconds microseconds()
	{
		const auto instance = reinterpret_cast<PIT_Type*>(pitBase);
		const auto count	= PIT_GetLifetimeTimerCount(instance);
		return convertLifeTimeToTime(count);
	}

#else

	static std::chrono::microseconds microseconds()
	{
		const auto instance = reinterpret_cast<PIT_Type*>(pitBase);
		const auto high		= PIT_GetCurrentTimerCount(instance, kPIT_Chnl_1);
		const auto low		= PIT_GetCurrentTimerCount(instance, kPIT_Chnl_0);
		const auto count	= (static_cast<uint64_t>(high) << 32) | low;
		return convertLifeTimeToTime(count);
	}

#endif


	static void delay (std::chrono::microseconds microToBusyWait)
	{
		const auto start = microseconds();
		while (microseconds() - start < microToBusyWait) {};
	}

private:
	static std::chrono::microseconds convertLifeTimeToTime (uint64_t liveTimeCount)
	{
		const auto clockFrequency	= CLOCK_GetFreq(clockSource);
		const auto sec				= std::chrono::seconds{secondsDowncountingMax - uint32_t(liveTimeCount >> 32U)};
		const auto lowCount			= msGetter{}() - uint32_t(0xFFFFFFFF & liveTimeCount);
		const auto microsec			= std::chrono::milliseconds{COUNT_TO_USEC(lowCount, clockFrequency)};
		return sec + microsec;
	}
};

} /* namespace Driver */

#endif /* DRIVERS_MONOTONICCLOCK_H_ */
