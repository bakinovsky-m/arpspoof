#include <iostream>
#include <cstdint>

#include "arppacket.h"

struct EthernetPacket{
    uint8_t destinationMAC[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    uint8_t sourceMAC[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t arpPacket[28] = {0};
};

int main(int argc, char* argv[])
{
    ARPPacket arp;
    EthernetPacket eth;

    uint8_t qwe[] = {1,23,4,5,6,7};
    arp.setTargetHwAddr(qwe);

    std::cout << sizeof(arp) << std::endl;
    std::cout << sizeof(eth) << std::endl;
    return 0;
}