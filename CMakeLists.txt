cmake_minimum_required (VERSION 3.16)
project (inx_debugger)

add_compile_options(-std=c++17)

include_directories(external/libelfin external/linenoise include)

add_executable(hello examples/hello_world.cpp)
set_target_properties(hello PROPERTIES COMPILE_FLAGS "-g -O0")

set(SOURCE_FILES 
    src/inxgdb.cpp
    src/debugger.hh
    src/debugger.cc
    src/common_helper.cc
    src/common_helper.hh
    src/breakpoint.hh
    src/breakpoint.cc
    src/registers.hh
    src/registers.cc
    )

add_executable(${PROJECT_NAME} ${SOURCE_FILES} external/linenoise/linenoise.c)


add_custom_target(
   libelfin
   COMMAND make
   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/external/libelfin
)
target_link_libraries(${PROJECT_NAME}
                      ${PROJECT_SOURCE_DIR}/external/libelfin/dwarf/libdwarf++.so
                      ${PROJECT_SOURCE_DIR}/external/libelfin/elf/libelf++.so)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_dependencies(inx_debugger libelfin)
