cmake_minimum_required(VERSION 3.0)
project(arpspoof)

add_definitions(-std=c++11 -Wall -Wno-narrowing)

add_executable(${PROJECT_NAME} main.cpp arppacket.cpp)

if(WIN32 OR MINGW OR CYGWIN)
    target_link_libraries(${PROJECT_NAME} ws2_32 iphlpapi)
endif()