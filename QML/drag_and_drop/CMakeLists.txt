cmake_minimum_required(VERSION 3.18)

project(drag_and_drop)

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/out CACHE STRING "output directory")
set(COMPILE_WARNING_ERROR_FLAGS "-Wall -Werror -Wdocumentation -Wno-unused-function")

make_directory(${OUTPUT_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 5.15.2 COMPONENTS Core REQUIRED)

add_subdirectory(Application)
add_custom_target(FullApp)
add_dependencies(FullApp Application)
