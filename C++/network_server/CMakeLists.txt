cmake_minimum_required(VERSION 3.14)
project(network_server)

set(CMAKE_CXX_STANDARD 14)

add_executable(network_server main.cpp abstract_medium.cpp network_server.cpp network_server.h server_socket.cpp server_socket.h server_connection.cpp server_connection.h)