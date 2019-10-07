cmake_minimum_required(VERSION 3.14)
project(proxy)

set(CMAKE_CXX_STANDARD 14)

add_executable(proxy main.cpp tcp_server.cpp tcp_server.h)