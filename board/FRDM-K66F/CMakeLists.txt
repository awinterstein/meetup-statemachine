add_library(board OBJECT
    board
    clock_config
    peripherals
    pin_mux
    startup_mk66f18
    system_MK66F18)

target_include_directories(board PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_SOURCE_DIR}/CMSIS)

add_object_dependencies(board sdk_drivers)


