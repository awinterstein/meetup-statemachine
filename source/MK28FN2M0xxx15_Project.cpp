/*
 * Copyright 2016-2018 NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MK28FN2M0xxx15_Project.cpp
 * @brief   Application entry point.
 */
#include <board.h>
#include <clock_config.h>
#include <stdio.h>
#include "MK28F15.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

#include <peripherals.h>
#include <pin_mux.h>

#include <CharDisplay.h>
#include <GPIOPin.h>
#include <ParallelBus.h>
#include <ADCChannelSingle.h>
#include <ButtonOverADC.h>

/* TODO: insert other definitions and declarations here. */
DECLARE_PIN_AS(BOARD_INITPINS_LCD_D7, LCD_D7);
DECLARE_PIN_AS(BOARD_INITPINS_LCD_D6, LCD_D6);
DECLARE_PIN_AS(BOARD_INITPINS_LCD_D5, LCD_D5);
DECLARE_PIN_AS(BOARD_INITPINS_LCD_D4, LCD_D4);
DECLARE_PIN_AS(BOARD_INITPINS_LCD_EN, LCD_EN);
DECLARE_PIN_AS(BOARD_INITPINS_LCD_RS, LCD_RS);

using LCD_DATABUS = Driver::ParallelBus<LCD_D4, LCD_D5, LCD_D6, LCD_D7>;
using DISPLAY = Driver::CharDisplay<LCD_RS, LCD_EN, LCD_DATABUS>;

DECLARE_ADC_CHANNEL_AS(BUTTON_ADC, 0, BUTTON_ADC);

using BUTTON_UP = Driver::ButtonOverADC<BUTTON_ADC, 1000lu, 100lu>;

/*
 * @brief   Application entry point.
 */
int main(void) {
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
	BOARD_InitDebugConsole();

    PRINTF("Hello World\n");

    volatile static bool lcdtestTrigger = false;
    if (lcdtestTrigger)
    {
    	DISPLAY::init();
    	DISPLAY::writeTopLine("Button adc %.3f", BUTTON_ADC::getVoltage());
    	DISPLAY::writeBottomLine("Button up: %c", BUTTON_UP::isPressed() ? 'h' : 'l');
    }

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;

    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
    }
    return 0 ;
}
