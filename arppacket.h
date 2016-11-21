#ifndef HG_ETHPACKET_H
#define HG_ETHPACKET_H

#include <cstdint>
#include <string>
// #include <arpa/inet.h>

/**
    ARP header:
        hardware 2 bytes
        protocol 2 bytes
        hardware length 1 byte
        protocol length 1 byte

        operation code 2 bytes

        source hardware address 6 bytes
        source protocol address 4 bytes
        target hardware address 6 bytes
        target protocol address 4 bytes
**/
#define ETHER_TYPE_FOR_ARP 0x0806
#define HW_TYPE_FOR_ETHER 0x0001
struct ARPPacket{
    ARPPacket() = default;
    uint16_t hardware = HW_TYPE_FOR_ETHER;
    uint16_t protocol = ETHER_TYPE_FOR_ARP;
    uint8_t hardwareLength = 6;
    uint8_t protocolLength = 4;

    uint16_t operationCode = 1; //response

    uint8_t sourceHardwareAddress[6]{0}; // random?
    uint8_t sourceProtocolAddress[4]{0}; // random?
    uint8_t targetHardwareAddress[6]{0};
    uint8_t targetProtocolAddress[4]{0};
};

/**
    Ethernet frame:
        destination MAC 6 bytes
        source MAC 6 bytes

        everything
**/
class EthernetPacket{
public:
    EthernetPacket() = default;
    uint8_t sourceMAC[6]{0};
    uint8_t targetMAC[6]{0};

    ARPPacket arp;


    void setSourceMAC(const uint8_t * sourcemac);
    void setTargetMAC(const uint8_t * targetmac);

    void setSourceIP(const uint8_t * srcIP);
    void setTargetIP(const uint8_t * trgIP);

    std::string toString() const;
};

// void sendPacket();

#endif