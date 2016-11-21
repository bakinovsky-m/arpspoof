#include "arppacket.h"

// void EthernetPacket::sendPacket(){
    
// }

void EthernetPacket::setSourceMAC(const uint8_t * srcmac){
    for(std::ptrdiff_t it = 0; it < arp.hardwareLength; it += 1){
        sourceMAC[it] = srcmac[it];
        arp.sourceHardwareAddress[it] = srcmac[it];
    }
}

void EthernetPacket::setTargetMAC(const uint8_t * trgmac){
    for (std::ptrdiff_t it = 0; it < arp.hardwareLength; it += 1){
        targetMAC[it] = trgmac[it];
        arp.targetHardwareAddress[it] = trgmac[it];
    }
}

void EthernetPacket::setSourceIP(const uint8_t * srcIP){
    for (std::ptrdiff_t it = 0; it < arp.protocolLength; it += 1){
        arp.sourceProtocolAddress[it] = srcIP[it];
    }
}

void EthernetPacket::setTargetIP(const uint8_t * trgIP){
    for (std::ptrdiff_t it = 0; it < arp.protocolLength; it += 1){
        arp.targetProtocolAddress[it] = trgIP[it];
    }
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