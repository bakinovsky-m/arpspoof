#include <iostream>
#include <unistd.h> /* usleep() */
#include "arppacket.hpp"

int main(int argc, char* argv[])
{
    // if(argc == 1){
    //     std::cout << "Help: ./arpspoof sourceMAC targetMAC sourceIP targetIP interface" << std::endl;
    //     return 0;
    // }

    EthernetPacket eth = EthernetPacket("192.168.1.1", "192.168.1.2", "00:00:00:00:00:00", "00:00:00:00:00:00");
    std::cout << eth << std::endl;

    EthernetPacket * e = &eth;
    while(1){
        if(argc != 6){
            std::string ifname = "lo\0";
            sendPacket(e, ifname);
        } else {
            sendPacket(e, argv[5]);
        }
        // std::cout << "reply sent" << std::endl;
        usleep(5*1000000);
    }

    delete e;


    return 0;
}