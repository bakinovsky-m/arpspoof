#include "ethpacket.h"

void EthernetPacket::setSourceMAC(const uint8_t * srcmac){
    // for (int i = 0; i < 6; i++){
    //     sourceMAC[i] = sourcemac[i];
    //     arp.sourceHardwareAddress[i] = sourcemac[i];
    // }
    for(std::ptrdiff_t it = 0; it < arp.hardwareLength; it += 1){
        sourceMAC[it] = srcmac[it];
        arp.sourceHardwareAddress[it] = srcmac[it];
    }
}

void EthernetPacket::setTargetMAC(const uint8_t * trgmac){
    //for (int i = 0; i < 6; i++){
    for (std::ptrdiff_t it = 0; it < arp.hardwareLength; it += 1){
        targetMAC[it] = trgmac[it];
        arp.targetHardwareAddress[it] = trgmac[it];
    }
}

void EthernetPacket::setSourceIP(const uint8_t * srcIP){

}

void EthernetPacket::setTargetIP(const uint8_t * trgIP){

}

std::string EthernetPacket::toString() const{
    std::string str = "";
    str += "destmac: ";
    for (int i = 0; i < 6; i++){
        str += std::to_string(targetMAC[i]);
        str += " ";
    }
    str += "\n";

    str += "sourcemac: ";
    for (int i = 0 ; i < 6; i++){
        str += std::to_string(sourceMAC[i]);
        str += " ";
    }
    return str;
}
