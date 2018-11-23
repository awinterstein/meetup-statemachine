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

	static std::chrono::microseconds microseconds()
	{
		const auto highReg		= PIT_GetCurrentTimerCount(reinterpret_cast<PIT_Type*>(pitBase), kPIT_Chnl_1);
		const auto lowReg		= PIT_GetCurrentTimerCount(reinterpret_cast<PIT_Type*>(pitBase), kPIT_Chnl_0);

		const auto highCount	= secondsDowncountingMax - highReg;
		const auto sec			= std::chrono::seconds{highCount};

		const auto lowCount		= msGetter{}() - lowReg;
		const auto microsec		= std::chrono::microseconds{COUNT_TO_USEC(lowCount, CLOCK_GetFreq(clockSource))};

		return sec + microsec;
	}

	static void delay (std::chrono::microseconds microToBusyWait)
	{
		const auto start = microseconds();
		while (true)
		{
			const auto delta = microseconds() - start;
			if (delta > microToBusyWait)
			{
				break;
			}
		};
	}
};

} /* namespace Driver */

#endif /* DRIVERS_MONOTONICCLOCK_H_ */
