#ifndef BUTTON_EVENT__SOURCE____H___
#define BUTTON_EVENT__SOURCE____H___

#include "HAL.hpp"

namespace HAL
{

template<typename T>
class ButtonEventSource
{
private:
	static bool _alreadyHandedEventOver;

public:
	static bool shouldTriggerEvent()
	{
		if (T::isPressed())
		{
			if (!_alreadyHandedEventOver)
			{
				_alreadyHandedEventOver = true;
				return true;
			}
		}
		else
		{
			_alreadyHandedEventOver = false;
		}
		return false;
	}
};

template<typename T>
bool ButtonEventSource<T>::_alreadyHandedEventOver = false;

using EVENT_SOURCE_BUTTON_LEFT 	= ButtonEventSource<BUTTON_LEFT>;
using EVENT_SOURCE_BUTTON_RIGHT	= ButtonEventSource<BUTTON_RIGHT>;
using EVENT_SOURCE_BUTTON_UP 	= ButtonEventSource<BUTTON_UP>;
using EVENT_SOURCE_BUTTON_DOWN 	= ButtonEventSource<BUTTON_DOWN>;

}


#endif
