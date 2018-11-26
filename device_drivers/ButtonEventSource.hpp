#ifndef BUTTON_EVENT__SOURCE____H___
#define BUTTON_EVENT__SOURCE____H___

#include "HAL.hpp"

namespace HAL
{

template<typename T>
class ButtonEventSource
{
private:
	bool _alreadyHandedEventOver = false;

public:
	bool shouldTriggerEvent()
	{
		if (T::isPressed())
		{
			if (! _alreadyHandedEventOver)
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

extern ButtonEventSource<BUTTON_RIGHT> eventSourceRightButton;
extern ButtonEventSource<BUTTON_LEFT> eventSourceLeftButton;
extern ButtonEventSource<BUTTON_UP> eventSourceUpButton;
extern ButtonEventSource<BUTTON_DOWN> eventSourceDownButton;
}

#endif
