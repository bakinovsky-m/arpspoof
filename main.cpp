#include <iostream>
#include <cstdint>

// #include "arppacket.h"
#include "ethpacket.h"

int main(int argc, char* argv[])
{
    EthernetPacket eth;

    uint8_t destmac[] = {0xFF,23,4,5,6,7};
    uint8_t srcmac[] = {1,2, 3,4,5,6,7};
    eth.setDestinationMAC(destmac);
    eth.setSourceMAC(srcmac);

    std::cout << eth.toString() << std::endl;
    return 0;
}