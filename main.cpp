#include <iostream>
#include "arppacket.h"

int main(int argc, char* argv[])
{
    if(argc == 1){
        std::cout << "Help: ./arpspoof sourceMAC targetMAC sourceIP targetIP" << std::endl;
        // return 0;
    }

    EthernetPacket eth;
    std::cout << sizeof(eth) <<  std::endl;

    eth.parseIP(argv[1]);

    uint8_t srcMAC[] = {1,2, 3,4,5,6,7};
    uint8_t trgMAC[] = {0xFF,23,4,5,6,7};
    uint8_t srcIP[] = {192, 168, 1, 2};
    uint8_t trgIP[] = {192, 168, 1, 1};
    eth.setSourceMAC(srcMAC);
    eth.setTargetMAC(trgMAC);
    eth.setSourceIP(srcIP);
    eth.setTargetIP(trgIP);

    // sendPacket();

    std::cout << eth.toString() << std::endl;
    return 0;
}