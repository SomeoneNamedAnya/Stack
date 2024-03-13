cmake_minimum_required(VERSION 3.14)
project(Main VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(my_stack)
add_executable(main main.cpp)

set(SOURCE_LIB ./parser/scr/parser.cpp)
set(HEADER_LIB ./parser/include/parser.h)

add_library(parser ${SOURCE_LIB} ${HEADER_LIB})

set(SOURCE_LIB_2 ./parser/scr/parser.cpp)
set(HEADER_LIB_2 ./parser/include/parser.h)

add_library(command ${SOURCE_LIB_2} ${HEADER_LIB_2})


target_link_libraries(main mystack)
target_link_libraries(main parser)
target_link_libraries(main command)

target_include_directories(main PUBLIC
                          "my_stack"
                          "my_stack/include"
                          "parser/include"
                          "command/include"
                         )

add_compile_options("-O2")
