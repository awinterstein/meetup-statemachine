/*
 * HAL.hpp
 *
 *  Created on: Nov 10, 2018
 *      Author: vagrant
 */

#ifndef HAL_HPP_
#define HAL_HPP_

#include "MK28F15.h"

#include <CharDisplay.h>
#include <GPIOPin.h>
#include <ParallelBus.h>
#include <ADCChannelSingle.h>
#include <ButtonOverADC.h>
#include <Wire.h>

#include <macro_push.h>

using LCD_D7		= Driver::GPIOPin<BOARD_INITPINS_LCD_D7_GPIO, BOARD_INITPINS_LCD_D7_PIN>;
using LCD_D6		= Driver::GPIOPin<BOARD_INITPINS_LCD_D6_GPIO, BOARD_INITPINS_LCD_D6_PIN>;
using LCD_D5		= Driver::GPIOPin<BOARD_INITPINS_LCD_D5_GPIO, BOARD_INITPINS_LCD_D5_PIN>;
using LCD_D4		= Driver::GPIOPin<BOARD_INITPINS_LCD_D4_GPIO, BOARD_INITPINS_LCD_D4_PIN>;
using LCD_DATABUS	= Driver::ParallelBus<LCD_D4, LCD_D5, LCD_D6, LCD_D7>;

using LCD_EN		= Driver::GPIOPin<BOARD_INITPINS_LCD_EN_GPIO, BOARD_INITPINS_LCD_EN_PIN>;
using LCD_RS		= Driver::GPIOPin<BOARD_INITPINS_LCD_RS_GPIO, BOARD_INITPINS_LCD_RS_PIN>;
using DISPLAY		= Driver::CharDisplay<LCD_RS, LCD_EN, LCD_DATABUS>;

using COMMON_ADC	= Driver::ADCChannelSingle<BUTTON_ADC_PERIPHERAL, BUTTON_ADC_channelsConfig, 3300, 12>;
using BUTTON_UP		= Driver::ButtonOverADC<COMMON_ADC, 1000lu, 100lu>;

#include <macro_pop.h>

#endif /* HAL_HPP_ */
