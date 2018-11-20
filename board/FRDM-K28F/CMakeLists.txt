add_library(board OBJECT
    board
    clock_config
    peripherals
    pin_mux
    startup_mk28f15
    system_MK28F15)

target_include_directories(board PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_SOURCE_DIR}/CMSIS)

add_object_dependencies(board sdk_drivers)


