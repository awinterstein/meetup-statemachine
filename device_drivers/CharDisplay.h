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

#include <array>
#include <stdint.h>

namespace DRVR {

namespace {
#warning "Replace by something that makes more sense"
	static void delayMicroSec (uint32_t uSec)
	{
		for (uint64_t volatile i = uSec * 1000 ; i ; i--) {}
	}
}

template <typename registerSelect, typename enablaData, typename dataBus>
class CharDisplay {
public:
	using DisplayLine = std::array<const char, 16>;

	static void init()
	{
		enablaData::set();
	    registerSelect::clr();
	    DRVR::delayMicroSec(15000u);

	    for (int32_t i=3; i>0; i--)
	    {
	        writeByte(0x3);
	        DRVR::delayMicroSec(1640u);
	    }

	    writeByte(0x2);
	    DRVR::delayMicroSec(40u);

	    writeCommand(0x28);
	    writeCommand(0x0C);
	    writeCommand(0x6);
	    cls();
	}

	static void cls()
	{
		writeCommand(0x01);
		DRVR::delayMicroSec(1640u);
	}

	static void writeTopLine(const DisplayLine& line)
	{
		writeLine(line, 0u);
	}

	static void writeBottomLine(const DisplayLine& line)
	{
		writeLine(line, 1u);
	}

private:
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
	    delayMicroSec(40);
	    enablaData::clr();
	    delayMicroSec(40);
	    enablaData::set();

		dataBus::setBytes(value >> 0);
	    delayMicroSec(40);
	    enablaData::clr();
	    delayMicroSec(40);
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

	static void writeLine (const DisplayLine& line, uint32_t row)
	{
		for (auto& c : line)
		{
			const auto column = &c - line.data();
			character(column, row, c);
		}
	}
};

} /* namespace DRVR */

#endif /* DRIVERS_CHARDISPLAY_H_ */
