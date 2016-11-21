#include "arppacket.h"

// void EthernetPacket::sendPacket(){
    
// }

void EthernetPacket::setSourceMAC(const unsigned char * srcmac){
    for(std::ptrdiff_t it = 0; it < arp.hardwareLength; it += 1){
        sourceMAC[it] = srcmac[it];
        arp.sourceHardwareAddress[it] = srcmac[it];
    }
}

void EthernetPacket::setTargetMAC(const unsigned char * trgmac){
    for (std::ptrdiff_t it = 0; it < arp.hardwareLength; it += 1){
        targetMAC[it] = trgmac[it];
        arp.targetHardwareAddress[it] = trgmac[it];
    }
}

void EthernetPacket::setSourceIP(const unsigned char * srcIP){
    for (std::ptrdiff_t it = 0; it < arp.protocolLength; it += 1){
        arp.sourceProtocolAddress[it] = srcIP[it];
    }
}

void EthernetPacket::setTargetIP(const unsigned char * trgIP){
    for (std::ptrdiff_t it = 0; it < arp.protocolLength; it += 1){
        arp.targetProtocolAddress[it] = trgIP[it];
    }
}

unsigned char * EthernetPacket::parseIP(char * str){
    int b1, b2, b3, b4;
    char dot;
    std::istringstream s(str);

    s >> b1 >> dot >> b2 >> dot >> b3 >> dot >> b4;
    std::cout << b1 << std::endl;
    std::cout << b2 << std::endl;
    std::cout << b3 << std::endl;
    std::cout << b4 << std::endl;
    std::cout << (unsigned char)b1 << std::endl;
    std::cout << (unsigned char)b4 << std::endl;
    unsigned char qwe = (unsigned char) b1;
    return &qwe;
}

std::string EthernetPacket::toString() const{
    std::string str = "";

    str += "source mac: ";
    for (std::ptrdiff_t i = 0 ; i < arp.hardwareLength; i++){
        str += std::to_string(sourceMAC[i]);
        str += " ";
    }
    str += "\n";

    str += "target mac: ";
    for (std::ptrdiff_t i = 0; i < arp.hardwareLength; i++){
        str += std::to_string(targetMAC[i]);
        str += " ";
    }
    str += "\n";

    str += "source ip: ";
    for (std::ptrdiff_t i = 0 ; i < arp.protocolLength; i++){
        str += std::to_string(arp.sourceProtocolAddress[i]);
        str += " ";
    }
    str += "\n";

    str += "target ip: ";
    for (std::ptrdiff_t i = 0 ; i < arp.protocolLength; i++){
        str += std::to_string(arp.targetProtocolAddress[i]);
        str += " ";
    }
    return str;
}