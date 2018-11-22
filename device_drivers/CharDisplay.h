/* mbed TextLCD Library, for a 4-bit LCD based on HD44780
 * Copyright (c) 2007-2010, sford, http://mbed.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef DRIVERS_CHARDISPLAY_H_
#define DRIVERS_CHARDISPLAY_H_

#include <stdint.h>
#include <array>
#include <cstdio>
#include <cstdarg>

namespace Driver {

using namespace std::chrono_literals;

template <typename registerSelect, typename enablaData, typename dataBus, typename monoClock>
class CharDisplay {
public:
	using DisplayLine = std::array<char, 16>;

	static void init()
	{
		enablaData::set();
	    registerSelect::clr();

	    monoClock::delay(15ms);

	    for (int32_t i=3; i>0; i--)
	    {
	        writeByte(0x3);
	        monoClock::delay(3ms);
	    }

	    writeByte(0x2);
	    monoClock::delay(2ms);

	    writeCommand(0x28);
	    writeCommand(0x0C);
	    writeCommand(0x6);
	    cls();
	}

	static void cls()
	{
		writeCommand(0x01);
		monoClock::delay(3ms);
	}

	template<typename... Targs>
	static void writeTopLine(const char* fmt, Targs... args)
	{
		const auto line = writeBuffer(fmt, args...);
		writeLine(0, line);
	}

	template<typename... Targs>
	static void writeBottomLine(const char* fmt, Targs... args)
	{
		const auto line = writeBuffer(fmt, args...);
		writeLine(1, line);
	}

private:
	using TerminatedBuffer = std::array<char, sizeof(DisplayLine) + 1>;

	static int32_t address (const uint32_t column, const uint32_t row)
	{
		return 0x80 + (row * 0x40) + column;
	}

	static void character (const uint32_t column, const uint32_t row, const int32_t c)
	{
		const auto cursorSet = address(column, row);
		writeCommand(cursorSet);
		writeData(c);
	}

	static void writeByte (const int32_t value)
	{
		dataBus::setBytes(value >> 4);
		monoClock::delay(2ms);
	    enablaData::clr();
	    monoClock::delay(2ms);
	    enablaData::set();

		dataBus::setBytes(value >> 0);
		monoClock::delay(2ms);
	    enablaData::clr();
	    monoClock::delay(2ms);
	    enablaData::set();
	}

	static void writeCommand (const int32_t command)
	{
		registerSelect::clr();
		writeByte(command);
	}

	static void writeData (const int32_t data)
	{
		registerSelect::set();
		writeByte(data);
	}

	static void writeLine (uint32_t row, const DisplayLine& buffer)
	{
	    for (auto& c : buffer)
		{
			const auto column = &c - buffer.data();
			if (isprint(c))
			{
				character(column, row, c);
			}
			else
			{
				character(column, row, ' ');
			}
		}
	}

	template<typename... Targs>
	static DisplayLine writeBuffer (const char* fmt, Targs... args)
	{
		TerminatedBuffer buffer;
		snprintf(buffer.data(), buffer.size(), fmt, args...);

		DisplayLine line;
		line.fill(0x00);
		strncpy(line.data(), buffer.data(),line.size());
		return line;
	}
};

} /* namespace Driver */

#endif /* DRIVERS_CHARDISPLAY_H_ */
