cmake_minimum_required(VERSION 3.14)
project(Stack VERSION 0.1.0 LANGUAGES C CXX)

include_directories("include/")

set(SOURCE_EXE main.cpp)
set(SOURCE_LIB scr/Stack.cpp)	

add_library(longnum ${SOURCE_LIB} include/Stack.h)

#add_executable(main ${SOURCE_EXE})
#target_link_libraries(main longnum)	

add_compile_options("-O2")
