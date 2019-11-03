cmake_minimum_required(VERSION 3.14)
project(network_client)

set(CMAKE_CXX_STANDARD 14)

add_executable(network_client main.cpp network_client/network_client.cpp network_client/network_client.h network_client/socket/client_socket.cpp network_client/socket/client_socket.h)