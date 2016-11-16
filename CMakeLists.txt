cmake_minimum_required(VERSION 3.0)
project(arpspoof)
add_definitions(-std=c++11 -Wall -lboost)
add_executable(${PROJECT_NAME} main.cpp ethpacket.cpp)