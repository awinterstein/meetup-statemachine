cmake_minimum_required(VERSION 3.10)

project(statemachine_meetup_2018)

include(cmake/build-helpers.cmake)

set(HARDWARE_PLATFORM "FRDM-K28F" CACHE STRING "The hardware platform the firmware should be compiled for")
set_property(CACHE HARDWARE_PLATFORM PROPERTY STRINGS FRDM-K28F FRDM-K64F FRDM-K66F)

if (HARDWARE_PLATFORM STREQUAL "FRDM-K28F")
    set(CPU MK28FN2M0VMI15)
    set(CMAKE_LAUNCH_CPU MK28FN2M0xxx15)
elseif (HARDWARE_PLATFORM STREQUAL "FRDM-K64F")
    set(CPU MK64FN1M0VLL12)
    set(CMAKE_LAUNCH_CPU MK64FN1M0xxx12)
elseif (HARDWARE_PLATFORM STREQUAL "FRDM-K66F")
    set(CPU MK66FN2M0VMD18)
    set(CMAKE_LAUNCH_CPU MK66FN2M0xxx18)
endif ()

set(EXTRA_CXX_FLAGS "-std=c++14")
add_definitions(-D__NEWLIB__ -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DSDK_OS_BAREMETAL -D__NEWLIB__ -DCPU_${CPU}_cm4 -DCPU_${CPU})

set(CMAKE_EXECUTABLE_FORMAT "ELF")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -fno-common -g3 -Wall -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb ${EXTRA_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS} -nostdlib ${EXTRA_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "-Xlinker --gc-sections -Xlinker -print-memory-usage")

add_subdirectory(board/${HARDWARE_PLATFORM}) 
add_subdirectory(sdk_drivers/${HARDWARE_PLATFORM})


macro(maker ext)
set(LAUNCH_EXECUTABLE_NAME ${HARDWARE_PLATFORM}-${ext})
add_executable(${LAUNCH_EXECUTABLE_NAME}
  ${ARGN}
  source/setup.cpp source/semihost_hardfault.c device_drivers/HAL.cpp
	$<TARGET_OBJECTS:board>
	$<TARGET_OBJECTS:sdk_drivers>)         
target_include_directories(${LAUNCH_EXECUTABLE_NAME} PRIVATE source device_drivers utilities ~/boost/include DSL DSL/support)
add_object_dependencies(${LAUNCH_EXECUTABLE_NAME} board sdk_drivers)
configure_file("${CMAKE_SOURCE_DIR}/launch.cfg" "${CMAKE_BINARY_DIR}/${LAUNCH_EXECUTABLE_NAME}.launch")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Xlinker -Map=${LAUNCH_EXECUTABLE_NAME}.map")
endmacro(maker)

maker("DSL"         "source/DSL_main.cpp" ${CMAKE_CURRENT_SOURCE_DIR}/DSL/generated_state_machine_blinky.hpp)
maker("demo-HAL"    "source/demo_HAL.cpp")
maker("statechart"  "source/statechart.cpp")
maker("MSM"         "source/MSM.cpp")
maker("SML"         "source/SML.cpp")


add_custom_target(
        always_run_target ALL
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/DSL/generated_state_machine_blinky.hpp
)

add_custom_command(
        OUTPUT
            ${CMAKE_CURRENT_SOURCE_DIR}/DSL/generated_state_machine_blinky.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/DSL/generated_state_machine_blinky.cpp
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/DSL/blinky.sm
        COMMAND cd ~/statemachine_meetup_2018/DSL && python3 ~/Projects/state_machine_DSL/src/generate.py blinky.sm -path:/home/zuehlke/Projects/state_machine_DSL/templates
)

copy_linker_scripts()

