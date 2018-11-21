add_library(board OBJECT
    board
    clock_config
    peripherals
    pin_mux
    startup_mk64f12
    system_MK64F12)

target_include_directories(board PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_SOURCE_DIR}/CMSIS)

add_object_dependencies(board sdk_drivers)


