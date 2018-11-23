/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v4.1
processor: MK66FN2M0xxx18
package_id: MK66FN2M0VMD18
mcu_data: ksdk2_0
processor_version: 4.0.1
pin_labels:
- {pin_num: J12, pin_signal: CMP3_IN5/PTA25/MII0_TXCLK/FB_A28, label: LCD_D7, identifier: LCD_D7}
- {pin_num: A12, pin_signal: ADC0_SE4b/CMP1_IN0/TSI0_CH15/PTC2/SPI0_PCS2/UART1_CTS_b/FTM0_CH1/FB_AD12/SDRAM_A20/I2S0_TX_FS, label: LCD_D6, identifier: LCD_D6}
- {pin_num: D8, pin_signal: PTC5/LLWU_P9/SPI0_SCK/LPTMR0_ALT2/I2S0_RXD0/FB_AD10/SDRAM_A18/CMP0_OUT/FTM0_CH2, label: LCD_D5, identifier: LCD_D5}
- {pin_num: A7, pin_signal: PTC12/UART4_RTS_b/FTM_CLKIN0/FB_AD27/SDRAM_D27/FTM3_FLT0/TPM_CLKIN0, label: LCD_D4, identifier: LCD_D4}
- {pin_num: D12, pin_signal: TSI0_CH11/PTB18/CAN0_TX/FTM2_CH0/I2S0_TX_BCLK/FB_AD15/SDRAM_A23/FTM2_QD_PHA/TPM2_CH0, label: LCD_RS, identifier: LCD_RS}
- {pin_num: D11, pin_signal: TSI0_CH12/PTB19/CAN0_RX/FTM2_CH1/I2S0_TX_FS/FB_OE_b/FTM2_QD_PHB/TPM2_CH1, label: LCD_EN, identifier: LCD_EN}
- {pin_num: F11, pin_signal: ADC1_SE13/PTB7/FB_AD22/SDRAM_D22, label: BUTTON_ALL_ADC, identifier: BUTTON_ALL_ADC}
- {pin_num: F12, pin_signal: ADC1_SE12/PTB6/FB_AD23/SDRAM_D23, label: BLUE_OUT, identifier: BLUE_OUT}
- {pin_num: G9, pin_signal: ADC1_SE11/PTB5/ENET0_1588_TMR3/FTM2_FLT0, label: BLUE_IN, identifier: BLUE_IN}
- {pin_num: G11, pin_signal: ADC0_SE13/TSI0_CH8/PTB3/I2C0_SDA/UART0_CTS_b/UART0_COL_b/ENET0_1588_TMR1/SDRAM_CS0_b/FTM0_FLT0, label: RED_OUT, identifier: RED_OUT}
- {pin_num: G12, pin_signal: ADC0_SE12/TSI0_CH7/PTB2/I2C0_SCL/UART0_RTS_b/ENET0_1588_TMR0/SDRAM_WE/FTM0_FLT3, label: RED_IN, identifier: RED_IN}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: J12, peripheral: GPIOA, signal: 'GPIO, 25', pin_signal: CMP3_IN5/PTA25/MII0_TXCLK/FB_A28, direction: OUTPUT}
  - {pin_num: A12, peripheral: GPIOC, signal: 'GPIO, 2', pin_signal: ADC0_SE4b/CMP1_IN0/TSI0_CH15/PTC2/SPI0_PCS2/UART1_CTS_b/FTM0_CH1/FB_AD12/SDRAM_A20/I2S0_TX_FS,
    direction: OUTPUT}
  - {pin_num: D8, peripheral: GPIOC, signal: 'GPIO, 5', pin_signal: PTC5/LLWU_P9/SPI0_SCK/LPTMR0_ALT2/I2S0_RXD0/FB_AD10/SDRAM_A18/CMP0_OUT/FTM0_CH2, direction: OUTPUT}
  - {pin_num: A7, peripheral: GPIOC, signal: 'GPIO, 12', pin_signal: PTC12/UART4_RTS_b/FTM_CLKIN0/FB_AD27/SDRAM_D27/FTM3_FLT0/TPM_CLKIN0, direction: OUTPUT}
  - {pin_num: D12, peripheral: GPIOB, signal: 'GPIO, 18', pin_signal: TSI0_CH11/PTB18/CAN0_TX/FTM2_CH0/I2S0_TX_BCLK/FB_AD15/SDRAM_A23/FTM2_QD_PHA/TPM2_CH0, direction: OUTPUT}
  - {pin_num: D11, peripheral: GPIOB, signal: 'GPIO, 19', pin_signal: TSI0_CH12/PTB19/CAN0_RX/FTM2_CH1/I2S0_TX_FS/FB_OE_b/FTM2_QD_PHB/TPM2_CH1, direction: OUTPUT}
  - {pin_num: F11, peripheral: ADC1, signal: 'SE, 13', pin_signal: ADC1_SE13/PTB7/FB_AD22/SDRAM_D22}
  - {pin_num: F12, peripheral: GPIOB, signal: 'GPIO, 6', pin_signal: ADC1_SE12/PTB6/FB_AD23/SDRAM_D23, direction: OUTPUT}
  - {pin_num: G9, peripheral: GPIOB, signal: 'GPIO, 5', pin_signal: ADC1_SE11/PTB5/ENET0_1588_TMR3/FTM2_FLT0, direction: INPUT}
  - {pin_num: G11, peripheral: GPIOB, signal: 'GPIO, 3', pin_signal: ADC0_SE13/TSI0_CH8/PTB3/I2C0_SDA/UART0_CTS_b/UART0_COL_b/ENET0_1588_TMR1/SDRAM_CS0_b/FTM0_FLT0,
    direction: OUTPUT}
  - {pin_num: G12, peripheral: GPIOB, signal: 'GPIO, 2', pin_signal: ADC0_SE12/TSI0_CH7/PTB2/I2C0_SCL/UART0_RTS_b/ENET0_1588_TMR0/SDRAM_WE/FTM0_FLT3, direction: INPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);

    gpio_pin_config_t LCD_D7_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTA25 (pin J12)  */
    GPIO_PinInit(BOARD_INITPINS_LCD_D7_GPIO, BOARD_INITPINS_LCD_D7_PIN, &LCD_D7_config);

    gpio_pin_config_t RED_IN_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB2 (pin G12)  */
    GPIO_PinInit(BOARD_INITPINS_RED_IN_GPIO, BOARD_INITPINS_RED_IN_PIN, &RED_IN_config);

    gpio_pin_config_t RED_OUT_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB3 (pin G11)  */
    GPIO_PinInit(BOARD_INITPINS_RED_OUT_GPIO, BOARD_INITPINS_RED_OUT_PIN, &RED_OUT_config);

    gpio_pin_config_t BLUE_IN_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB5 (pin G9)  */
    GPIO_PinInit(BOARD_INITPINS_BLUE_IN_GPIO, BOARD_INITPINS_BLUE_IN_PIN, &BLUE_IN_config);

    gpio_pin_config_t BLUE_OUT_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB6 (pin F12)  */
    GPIO_PinInit(BOARD_INITPINS_BLUE_OUT_GPIO, BOARD_INITPINS_BLUE_OUT_PIN, &BLUE_OUT_config);

    gpio_pin_config_t LCD_RS_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB18 (pin D12)  */
    GPIO_PinInit(BOARD_INITPINS_LCD_RS_GPIO, BOARD_INITPINS_LCD_RS_PIN, &LCD_RS_config);

    gpio_pin_config_t LCD_EN_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB19 (pin D11)  */
    GPIO_PinInit(BOARD_INITPINS_LCD_EN_GPIO, BOARD_INITPINS_LCD_EN_PIN, &LCD_EN_config);

    gpio_pin_config_t LCD_D6_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC2 (pin A12)  */
    GPIO_PinInit(BOARD_INITPINS_LCD_D6_GPIO, BOARD_INITPINS_LCD_D6_PIN, &LCD_D6_config);

    gpio_pin_config_t LCD_D5_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC5 (pin D8)  */
    GPIO_PinInit(BOARD_INITPINS_LCD_D5_GPIO, BOARD_INITPINS_LCD_D5_PIN, &LCD_D5_config);

    gpio_pin_config_t LCD_D4_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC12 (pin A7)  */
    GPIO_PinInit(BOARD_INITPINS_LCD_D4_GPIO, BOARD_INITPINS_LCD_D4_PIN, &LCD_D4_config);

    /* PORTA25 (pin J12) is configured as PTA25 */
    PORT_SetPinMux(BOARD_INITPINS_LCD_D7_PORT, BOARD_INITPINS_LCD_D7_PIN, kPORT_MuxAsGpio);

    /* PORTB18 (pin D12) is configured as PTB18 */
    PORT_SetPinMux(BOARD_INITPINS_LCD_RS_PORT, BOARD_INITPINS_LCD_RS_PIN, kPORT_MuxAsGpio);

    /* PORTB19 (pin D11) is configured as PTB19 */
    PORT_SetPinMux(BOARD_INITPINS_LCD_EN_PORT, BOARD_INITPINS_LCD_EN_PIN, kPORT_MuxAsGpio);

    /* PORTB2 (pin G12) is configured as PTB2 */
    PORT_SetPinMux(BOARD_INITPINS_RED_IN_PORT, BOARD_INITPINS_RED_IN_PIN, kPORT_MuxAsGpio);

    /* PORTB3 (pin G11) is configured as PTB3 */
    PORT_SetPinMux(BOARD_INITPINS_RED_OUT_PORT, BOARD_INITPINS_RED_OUT_PIN, kPORT_MuxAsGpio);

    /* PORTB5 (pin G9) is configured as PTB5 */
    PORT_SetPinMux(BOARD_INITPINS_BLUE_IN_PORT, BOARD_INITPINS_BLUE_IN_PIN, kPORT_MuxAsGpio);

    /* PORTB6 (pin F12) is configured as PTB6 */
    PORT_SetPinMux(BOARD_INITPINS_BLUE_OUT_PORT, BOARD_INITPINS_BLUE_OUT_PIN, kPORT_MuxAsGpio);

    /* PORTB7 (pin F11) is configured as ADC1_SE13 */
    PORT_SetPinMux(BOARD_INITPINS_BUTTON_ALL_ADC_PORT, BOARD_INITPINS_BUTTON_ALL_ADC_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTC12 (pin A7) is configured as PTC12 */
    PORT_SetPinMux(BOARD_INITPINS_LCD_D4_PORT, BOARD_INITPINS_LCD_D4_PIN, kPORT_MuxAsGpio);

    /* PORTC2 (pin A12) is configured as PTC2 */
    PORT_SetPinMux(BOARD_INITPINS_LCD_D6_PORT, BOARD_INITPINS_LCD_D6_PIN, kPORT_MuxAsGpio);

    /* PORTC5 (pin D8) is configured as PTC5 */
    PORT_SetPinMux(BOARD_INITPINS_LCD_D5_PORT, BOARD_INITPINS_LCD_D5_PIN, kPORT_MuxAsGpio);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/