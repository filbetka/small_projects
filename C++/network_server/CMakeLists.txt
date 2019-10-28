cmake_minimum_required(VERSION 3.14)
project(network_server)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(network_server main.cpp network_server.cpp network_server.h server_socket.cpp server_socket.h server_connection.cpp server_connection.h server_listener.cpp server_listener.h)