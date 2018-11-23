cmake_minimum_required(VERSION 3.10)

project(statemachine_meetup_2018)

include(cmake/build-helpers.cmake)

set(HARDWARE_PLATFORM "FRDM-K28F" CACHE STRING "The hardware platform the firmware should be compiled for")
set_property(CACHE HARDWARE_PLATFORM PROPERTY STRINGS FRDM-K66F FRDM-K28F)

if (HARDWARE_PLATFORM STREQUAL "FRDM-K28F")
    set(CPU MK28FN2M0VMI15)
    set(CMAKE_LAUNCH_CPU MK28FN2M0xxx15)
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

set(LAUNCH_EXECUTABLE_NAME ${HARDWARE_PLATFORM})

add_subdirectory(board/${HARDWARE_PLATFORM}) 
add_subdirectory(sdk_drivers/${HARDWARE_PLATFORM})

add_executable(${HARDWARE_PLATFORM}
	source/MK28FN2M0xxx15_Project.cpp
	source/semihost_hardfault.c
	$<TARGET_OBJECTS:board>
	$<TARGET_OBJECTS:sdk_drivers>)
target_include_directories(${HARDWARE_PLATFORM} PRIVATE source device_drivers utilities)
add_object_dependencies(${HARDWARE_PLATFORM} board sdk_drivers)

configure_file("${CMAKE_SOURCE_DIR}/launch.cfg" "${CMAKE_BINARY_DIR}/${LAUNCH_EXECUTABLE_NAME}.launch")
copy_linker_scripts()
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Xlinker -Map=${LAUNCH_EXECUTABLE_NAME}.map")
