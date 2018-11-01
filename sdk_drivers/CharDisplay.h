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

namespace DRVR {

namespace {
	static void delayMicroSec (uint32_t uSec)
	{
		for (uint64_t volatile i = uSec * 1000 ; i ; i--) {}
	}
}

template <typename registerSelect, typename enablaData, typename dataBus>
class CharDisplay {
public:
	CharDisplay();
	virtual ~CharDisplay();

	static int32_t putc(int32_t c);

	#warning "Provide a print function"
	//int32_t printf(const char* format, ...);

	static void cls()
	{
		writeCommand(0x01);
		DRVR::delayMicroSec(1640u);
		locate(0, 0);
	}

private:
    static void locate (uint32_t column, uint32_t row)
    {
    	column_ = column;
    	row_ = row;
    }

    // int _putc (int value)
	static int32_t putCharOnDisplay (int32_t value)
	{
		if (value == '\n') {
			column_ = 0;
			row_++;
			if (row_ >= rows()) {
				row_ = 0;
			}
		}
		else
		{
			character(column_, row_, value);
			column_++;
			if (column_ >= columns()) {
				column_ = 0;
				row_++;
				if (row_ >= rows()) {
					row_ = 0;
				}
			}
		}
		return value;
	}

	static int32_t address (uint32_t column, uint32_t row)
	{
		return 0x80 + (row_ * 0x40) + column_;
	}

	static void character (uint32_t column, uint32_t row, int32_t c)
	{
		const auto cursorSet = address(column, row);
		writeCommand(cursorSet);
		writeData(c);
	}

	static uint32_t columns() { return 16; }
	static uint32_t rows() { return 2; }

	static void writeByte (int32_t value)
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

	static void writeCommand (int32_t command)
	{
		registerSelect::clr();
		writeByte(command);
	}

	static void writeData (int32_t data)
	{
		registerSelect::set();
		writeByte(data);
	}

	static uint32_t column_;
	static uint32_t row_;
};

} /* namespace DRVR */

#endif /* DRIVERS_CHARDISPLAY_H_ */
