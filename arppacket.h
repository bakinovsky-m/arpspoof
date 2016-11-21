#ifndef HG_ETHPACKET_H
#define HG_ETHPACKET_H

#include <string>
#include <sstream>
#include <iostream>


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
    unsigned short int hardware = HW_TYPE_FOR_ETHER;
    unsigned short int protocol = ETHER_TYPE_FOR_ARP;
    unsigned char hardwareLength = 6;
    unsigned char protocolLength = 4;

    unsigned short int operationCode = 1; //response

    unsigned char sourceHardwareAddress[6]{0};
    unsigned char sourceProtocolAddress[4]{0};
    unsigned char targetHardwareAddress[6]{0};
    unsigned char targetProtocolAddress[4]{0};
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
    unsigned char sourceMAC[6]{0};
    unsigned char targetMAC[6]{0};

    ARPPacket arp;


    void setSourceMAC(const unsigned char * sourcemac);
    void setTargetMAC(const unsigned char * targetmac);

    void setSourceIP(const unsigned char * srcIP);
    void setTargetIP(const unsigned char * trgIP);

    unsigned char * parseIP(char * str);

    std::string toString() const;
};

// void sendPacket();

#endif