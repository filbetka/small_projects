cmake_minimum_required(VERSION 3.15)
project(event_engine)

set(CMAKE_CXX_STANDARD 14)

add_executable(event_engine main.cpp engine.cpp engine.h object.cpp object.h connection.cpp connection.h events.cpp events.h)