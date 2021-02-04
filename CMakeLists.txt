cmake_minimum_required (VERSION 3.16)
project (inx_debugger)

add_compile_options(-std=c++17)

include_directories(external/libelfin external/linenoise include)
add_executable(${PROJECT_NAME} src/inxgdb.cpp ext/linenoise/linenoise.c)


add_custom_target(
   libelfin
   COMMAND make
   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/external/libelfin
)
target_link_libraries(minidbg
                      ${PROJECT_SOURCE_DIR}/external/libelfin/dwarf/libdwarf++.so
                      ${PROJECT_SOURCE_DIR}/external/libelfin/elf/libelf++.so)
add_dependencies(inx_debugger libelfin)
