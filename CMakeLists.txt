cmake_minimum_required(VERSION 3.14)
project(Main VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(my_stack)

add_executable(main main.cpp)
target_link_libraries(main mystack)

target_include_directories(main PUBLIC
                          "my_stack"
                          "my_stack/include"
                         )

add_compile_options("-O2")
