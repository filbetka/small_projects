cmake_minimum_required (VERSION 3.16)
project (example_tests VERSION 1.0)

add_executable (
    tests
    program.cpp
    tests.cpp
)

target_link_libraries (
    tests
    gtest
    pthread
)

