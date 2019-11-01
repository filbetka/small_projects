cmake_minimum_required(VERSION 3.14)
project(network_server)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(network_server main.cpp network_server/network_server.cpp network_server/network_server.h network_server/socket/server_socket.cpp network_server/socket/server_socket.h network_server/tools/server_connection.cpp network_server/tools/server_connection.h network_server/listener/server_listener.cpp network_server/listener/server_listener.h)