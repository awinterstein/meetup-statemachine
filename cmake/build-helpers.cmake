macro(ADD_OBJECT_DEPENDENCIES target)

    set(dependencies "${ARGN}")
    foreach(dependency IN LISTS dependencies)
    	target_include_directories(${target} PRIVATE $<TARGET_PROPERTY:${dependency},INCLUDE_DIRECTORIES>)
    endforeach()

endmacro()


macro(COPY_LINKER_SCRIPTS)

  configure_file(${CMAKE_SOURCE_DIR}/linking/${CPU}.ld ${CMAKE_CURRENT_BINARY_DIR}/)
  configure_file(${CMAKE_SOURCE_DIR}/linking/${CPU}_library.ld ${CMAKE_CURRENT_BINARY_DIR}/)
  configure_file(${CMAKE_SOURCE_DIR}/linking/${CPU}_memory.ld ${CMAKE_CURRENT_BINARY_DIR}/)

  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T \"${CMAKE_CURRENT_BINARY_DIR}/${CPU}.ld\"")

endmacro()

