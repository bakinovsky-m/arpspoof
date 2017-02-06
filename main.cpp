#include <iostream>
#include "arppacket.hpp"

int main(int argc, char* argv[])
{
    EthernetPacket eth = EthernetPacket("12:23:34:45:56:67", "21:32:43:54:65:76", "192.168.1.1", "192.168.1.2");
    std::cout << eth << std::endl;

    sendPacket(&eth, "lo");

    return 0;
}