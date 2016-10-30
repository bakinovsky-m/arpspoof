project(arpspoof)
add_definitions(-std=c++11)
add_executable(${PROJECT_NAME} main.cpp ethpacket.cpp)