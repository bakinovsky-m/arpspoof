#include "arppacket.h"

void ARPPacket::setTargetHwAddr(const uint8_t * hwaddr){
    for(int i = 0; i < 6; i++){
        targetHardwareAddress[i] = hwaddr[i];
    }
}