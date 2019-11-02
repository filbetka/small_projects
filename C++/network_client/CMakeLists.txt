cmake_minimum_required(VERSION 3.14)
project(network_client)

set(CMAKE_CXX_STANDARD 14)

add_executable(network_client main.cpp network_client.cpp network_client.h abstract_medium.cpp abstract_medium.h client_socket.cpp client_socket.h)