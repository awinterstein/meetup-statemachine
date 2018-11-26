#ifndef SUPPORT_BLINKY___H___
#define SUPPORT_BLINKY___H___

#include <HAL.hpp>

class Led
{
private:
	int id;
	bool state = false;

public:
	void init(int id)
	{
		this->id = id;
	}

	void on()
	{
		HAL::DISPLAY::writeTopLine("%d: on", id);
		state = true;
	}

	void off()
	{
		HAL::DISPLAY::writeTopLine("%d: off", id);
		state = false;
	}

	void toggle()
	{
		if (state)
		{
			off();
		}
		else
		{
			on();
		}
	}
};

static inline void init(Led &led, int id)
{
	led.init(id);
}

#endif

