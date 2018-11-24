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
		char buf[12];
		snprintf(buf, sizeof(buf), "%d: on", id);
		HAL::DISPLAY::writeTopLine(buf);
		state = true;
	}

	void off()
	{
		char buf[12];
		snprintf(buf, sizeof(buf), "%d: off", id);
		HAL::DISPLAY::writeTopLine(buf);
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

