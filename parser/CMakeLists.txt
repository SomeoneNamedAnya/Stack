cmake_minimum_required(VERSION 3.14)
project(my_stack VERSION 0.1.0 LANGUAGES C CXX)
include_directories(./include)

set(SOURCE_LIB ./scr/parser.cpp)
set(HEADER_LIB ./include/parser.h)

add_library(parser ${SOURCE_LIB} ${HEADER_LIB})
# target_include_directories(mystack PUBLIC MyStack)

# add_compile_options("-O2")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
