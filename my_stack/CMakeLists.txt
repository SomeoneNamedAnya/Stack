cmake_minimum_required(VERSION 3.14)
project(my_stack VERSION 0.1.0 LANGUAGES C CXX)
include_directories(./include)
set(HEADER_LIB ./include/mystack.h)

add_library(mystack ${HEADER_LIB})
# target_include_directories(mystack PUBLIC MyStack)

add_compile_options("-O2")
