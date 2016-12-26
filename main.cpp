#include <iostream>
// #include <unistd.h> /* usleep() */
#include "arppacket.hpp"

int main(int argc, char* argv[])
{
    // if(argc == 1){
    //     std::cout << "Help: ./arpspoof sourceMAC targetMAC sourceIP targetIP interface" << std::endl;
    //     return 0;
    // }

    EthernetPacket eth = EthernetPacket("12:23:34:45:56:67", "21:32:43:54:65:76", "192.168.1.1", "192.168.1.2");
    std::cout << eth << std::endl;

    // while(1){
    //     if(argc != 6){
    //         sendPacket(&eth, "lo");
    //     } else {
    //         sendPacket(&eth, argv[5]);
    //     }
    //     // std::cout << "reply sent" << std::endl;
    //     usleep(5*1000000);
    // }
    sendPacket(&eth, "lo");

    return 0;
}