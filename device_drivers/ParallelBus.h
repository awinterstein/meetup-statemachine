/*
 * Pin.h
 *
 *  Created on: 28 Oct 2018
 *      Author: meetup
 */

#ifndef DRIVERS_PARALLELBUS_H_
#define DRIVERS_PARALLELBUS_H_

#include "GPIOPin.h"

namespace Driver {

template <typename D1, typename D2, typename D3, typename D4>
class ParallelBus {
public:
	ParallelBus();
	virtual ~ParallelBus();

	static void setBytes (uint8_t byte)
	{
		if (byte & 1) { D1::set(); } else { D1::clr(); }
		if (byte & 2) { D2::set(); } else { D2::clr(); }
		if (byte & 4) { D3::set(); } else { D3::clr(); }
		if (byte & 8) { D4::set(); } else { D4::clr(); }
	}

	static void clrBytes ()
	{
		D1::clr();
		D2::clr();
		D3::clr();
		D4::clr();
	}
};

} /* namespace Driver */

#endif /* DRIVERS_PARALLELBUS_H_ */
