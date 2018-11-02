/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v4.1
processor: MK28FN2M0xxx15
package_id: MK28FN2M0VMI15
mcu_data: ksdk2_0
processor_version: 4.0.1
pin_labels:
- {pin_num: D7, pin_signal: PTC18/LPUART3_RTS_b/FB_TBST_b/FB_CS2_b/FB_BE15_8_BLS23_16_b/SDRAM_DQM1, label: LCD_D7, identifier: LCD_D7}
- {pin_num: B8, pin_signal: PTC13/LPUART4_CTS_b/FTM_CLKIN1/FB_AD26/SDRAM_D26/TPM_CLKIN1, label: LCD_D6, identifier: LCD_D6}
- {pin_num: B9, pin_signal: PTC12/LPUART4_RTS_b/FTM_CLKIN0/FB_AD27/SDRAM_D27/FTM3_FLT0/TPM_CLKIN0, label: LCD_D5, identifier: LCD_D5}
- {pin_num: A10, pin_signal: CMP0_IN0/PTC6/LLWU_P10/SPI0_SOUT/PDB0_EXTRG/I2S0_RX_BCLK/FB_AD9/SDRAM_A17/I2S0_MCLK/FXIO0_D14, label: LCD_D4, identifier: LCD_D4}
- {pin_num: C7, pin_signal: PTC19/LPUART3_CTS_b/FB_CS3_b/FB_BE7_0_BLS31_24_b/SDRAM_DQM0/FB_TA_b/QSPI0A_SS1_B, label: LCD_RS, identifier: LCD_RS}
- {pin_num: D11, pin_signal: PTB19/SDRAM_CKE/FTM2_CH1/I2S0_TX_FS/FB_OE_b/FTM2_QD_PHB/TPM2_CH1/FXIO0_D7, label: LCD_EN, identifier: LCD_EN}
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
  - {pin_num: D7, peripheral: GPIOC, signal: 'GPIO, 18', pin_signal: PTC18/LPUART3_RTS_b/FB_TBST_b/FB_CS2_b/FB_BE15_8_BLS23_16_b/SDRAM_DQM1, direction: OUTPUT}
  - {pin_num: B8, peripheral: GPIOC, signal: 'GPIO, 13', pin_signal: PTC13/LPUART4_CTS_b/FTM_CLKIN1/FB_AD26/SDRAM_D26/TPM_CLKIN1, direction: OUTPUT}
  - {pin_num: B9, peripheral: GPIOC, signal: 'GPIO, 12', pin_signal: PTC12/LPUART4_RTS_b/FTM_CLKIN0/FB_AD27/SDRAM_D27/FTM3_FLT0/TPM_CLKIN0, direction: OUTPUT}
  - {pin_num: A10, peripheral: GPIOC, signal: 'GPIO, 6', pin_signal: CMP0_IN0/PTC6/LLWU_P10/SPI0_SOUT/PDB0_EXTRG/I2S0_RX_BCLK/FB_AD9/SDRAM_A17/I2S0_MCLK/FXIO0_D14,
    direction: OUTPUT}
  - {pin_num: C7, peripheral: GPIOC, signal: 'GPIO, 19', pin_signal: PTC19/LPUART3_CTS_b/FB_CS3_b/FB_BE7_0_BLS31_24_b/SDRAM_DQM0/FB_TA_b/QSPI0A_SS1_B, direction: OUTPUT}
  - {pin_num: D11, peripheral: GPIOB, signal: 'GPIO, 19', pin_signal: PTB19/SDRAM_CKE/FTM2_CH1/I2S0_TX_FS/FB_OE_b/FTM2_QD_PHB/TPM2_CH1/FXIO0_D7, direction: OUTPUT}
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
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);

    gpio_pin_config_t LCD_EN_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB19 (pin D11)  */
    GPIO_PinInit(BOARD_INITPINS_LCD_EN_GPIO, BOARD_INITPINS_LCD_EN_PIN, &LCD_EN_config);

    gpio_pin_config_t LCD_D4_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC6 (pin A10)  */
    GPIO_PinInit(BOARD_INITPINS_LCD_D4_GPIO, BOARD_INITPINS_LCD_D4_PIN, &LCD_D4_config);

    gpio_pin_config_t LCD_D5_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC12 (pin B9)  */
    GPIO_PinInit(BOARD_INITPINS_LCD_D5_GPIO, BOARD_INITPINS_LCD_D5_PIN, &LCD_D5_config);

    gpio_pin_config_t LCD_D6_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC13 (pin B8)  */
    GPIO_PinInit(BOARD_INITPINS_LCD_D6_GPIO, BOARD_INITPINS_LCD_D6_PIN, &LCD_D6_config);

    gpio_pin_config_t LCD_D7_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC18 (pin D7)  */
    GPIO_PinInit(BOARD_INITPINS_LCD_D7_GPIO, BOARD_INITPINS_LCD_D7_PIN, &LCD_D7_config);

    gpio_pin_config_t LCD_RS_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC19 (pin C7)  */
    GPIO_PinInit(BOARD_INITPINS_LCD_RS_GPIO, BOARD_INITPINS_LCD_RS_PIN, &LCD_RS_config);

    /* PORTB19 (pin D11) is configured as PTB19 */
    PORT_SetPinMux(BOARD_INITPINS_LCD_EN_PORT, BOARD_INITPINS_LCD_EN_PIN, kPORT_MuxAsGpio);

    /* PORTC12 (pin B9) is configured as PTC12 */
    PORT_SetPinMux(BOARD_INITPINS_LCD_D5_PORT, BOARD_INITPINS_LCD_D5_PIN, kPORT_MuxAsGpio);

    /* PORTC13 (pin B8) is configured as PTC13 */
    PORT_SetPinMux(BOARD_INITPINS_LCD_D6_PORT, BOARD_INITPINS_LCD_D6_PIN, kPORT_MuxAsGpio);

    /* PORTC18 (pin D7) is configured as PTC18 */
    PORT_SetPinMux(BOARD_INITPINS_LCD_D7_PORT, BOARD_INITPINS_LCD_D7_PIN, kPORT_MuxAsGpio);

    /* PORTC19 (pin C7) is configured as PTC19 */
    PORT_SetPinMux(BOARD_INITPINS_LCD_RS_PORT, BOARD_INITPINS_LCD_RS_PIN, kPORT_MuxAsGpio);

    /* PORTC6 (pin A10) is configured as PTC6 */
    PORT_SetPinMux(BOARD_INITPINS_LCD_D4_PORT, BOARD_INITPINS_LCD_D4_PIN, kPORT_MuxAsGpio);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
