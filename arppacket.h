#ifndef HG_ETHPACKET_H
#define HG_ETHPACKET_H

#include <string>
#include <sstream>
#include <iostream>
#include <cstring>

#include <unistd.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
// #include <net/ethernet.h> /* the L2 protocols */
#include <linux/if_ether.h> /* the L2 protocols */
#include <arpa/inet.h>
#include <net/if.h>


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
#define HW_TYPE_FOR_ETHER 0x0001
// #define HW_TYPE_FOR_ETHER 0x0100
#define ETHER_TYPE_FOR_ARP 0x0800
// #define ETHER_TYPE_FOR_ARP 0x0608
struct ARPPacket{
    ARPPacket() = default;
    unsigned short int hardware = htons(HW_TYPE_FOR_ETHER);
    unsigned short int protocol = htons(ETHER_TYPE_FOR_ARP);
    unsigned char hardwareLength = 6;
    unsigned char protocolLength = 4;

    unsigned short int operationCode = htons(2); //response

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

    // unsigned char preamble[8]{0};
    unsigned char targetMAC[6]{0};
    unsigned char sourceMAC[6]{0};
    unsigned char type[2] = {0x08, 0x06};
    ARPPacket arp;


    void setSMAC(const char * sourcemac);
    void setTMAC(const char * targetmac);

    void setSIP(const char * srcIP);
    void setTIP(const char * trgIP);

    unsigned char * parseIP(const char * str);
    unsigned char * parseMAC(const char * str);

    std::string toString() const;
};

void sendPacket(const EthernetPacket * eth, const char * interface);

#endif