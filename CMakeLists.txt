cmake_minimum_required(VERSION 3.20)

project(Lab03 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(fraction src/fraction.cpp)
target_include_directories(fraction PUBLIC src)
add_library(fraction_set src/fraction_set.cpp)
target_include_directories(fraction_set PUBLIC src)
target_link_libraries(fraction_set PUBLIC fraction)

add_executable(lab_03 src/main.cpp)
target_link_libraries(lab_03 PRIVATE fraction_set)
enable_testing()

find_package(GTest CONFIG REQUIRED)

add_executable(lab_03_tests tests/test_fraction_set.cpp)

target_link_libraries(
    lab_03_tests
    PRIVATE
    fraction_set
    GTest::gtest_main
)

include(GoogleTest)
gtest_add_tests(TARGET lab_03_tests)