add_library(sdk_drivers OBJECT
    fsl_adc16
    fsl_clock
    fsl_common
    fsl_ftfx_cache
    fsl_ftfx_controller
    fsl_ftfx_flash
    fsl_ftfx_flexnvm
    fsl_gpio
    fsl_i2c
    fsl_lpuart
    fsl_pit
    fsl_rtc
    fsl_smc
)

target_include_directories(sdk_drivers PUBLIC
    ${CMAKE_CURRENT_LIST_DIR})

add_object_dependencies(sdk_drivers board)

