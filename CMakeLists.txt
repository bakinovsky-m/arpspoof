cmake_minimum_required(VERSION 3.0)
project(arpspoof)

add_definitions(-std=c++11 -Wall -Wno-narrowing)


if(BUILD_TYPE MATCHES "exe")
    add_executable(${PROJECT_NAME} main.cpp arppacket.cpp)
else()
    add_library(${PROJECT_NAME} arppacket.cpp arppacket.hpp)
endif()

if(WIN32 OR MINGW OR CYGWIN)
    target_link_libraries(${PROJECT_NAME} ws2_32 iphlpapi)
endif()