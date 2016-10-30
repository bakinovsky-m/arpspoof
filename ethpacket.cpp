#include "ethpacket.h"

void EthernetPacket::setSourceMAC(const uint8_t * sourcemac){
    for (int i = 0; i < 6; i++){
        sourceMAC[i] = sourcemac[i];
        arp.sourceHardwareAddress[i] = sourcemac[i];
    }
}

void EthernetPacket::setDestinationMAC(const uint8_t * destmac){
    for (int i = 0; i < 6; i++){
        destinationMAC[i] = destmac[i];
        arp.targetHardwareAddress[i] = destmac[i];
    }
}

std::string EthernetPacket::toString() const{
    std::string str = "";
    str += "destmac: ";
    for (int i =0;i<6;i++){
        str += std::to_string(destinationMAC[i]);
        str += " ";
    }
    str += "\n";

    str += "sourcemac: ";
    for (int i =0;i<6;i++){
        str += std::to_string(sourceMAC[i]);
        str += " ";
    }
    return str;
}