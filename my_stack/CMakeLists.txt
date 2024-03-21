cmake_minimum_required(VERSION 3.14)
project(my_stack VERSION 0.1.0 LANGUAGES C CXX)
include_directories(./include)

set(SOURCE_LIB ./scr/mystack.cpp)
set(HEADER_LIB ./include/mystack.h)

add_library(mystack ${SOURCE_LIB} ${HEADER_LIB})
# target_include_directories(mystack PUBLIC MyStack)
target_link_libraries(mystack)
# add_compile_options("-O2")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests test/tests.cpp)
target_link_libraries(tests mystack GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
