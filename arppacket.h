#ifndef HG_ETHPACKET_H
#define HG_ETHPACKET_H

// #include <string>
#include <sstream> /* istringstream */
// #include <iostream> /* cout's */
#include <cstdio> /* sscanf() */

// cross platform?
#if defined __WIN32 || defined __WIN64 || defined __MINGW32__ || defined __MINGW64__ || defined __CYGWIN__ || defined __WINDOWS__

#include <winsock2.h>
#include <ws2tcpip.h>
#include "custom_for_win.h" /* my custom header with some definitions */

#else

#include <sys/socket.h> /* nothing needs this header */
#include <linux/if_packet.h> /* sockaddr_ll */
#include <linux/if_ether.h> /* ETH_P_ARP, ETH_ALEN */
#include <arpa/inet.h> /* htons() */
#include <net/if.h> /* if_nametoindex() */

#endif

#include <unistd.h> /* close() */

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
/* 
    ether type must be 0806 for arp, 
    but i changed it to 0080 for ip
    because of wireshark view.
    need to test, maybe 0806 will work too
    TESTED
 */
#define ETHER_TYPE_FOR_ARP 0x0806
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
        type 2 bytes
        
        everything
**/
class EthernetPacket{
public:
    EthernetPacket() = default;

    unsigned char targetMAC[6]{0};
    unsigned char sourceMAC[6]{0};
    unsigned char type[2] = {0x08, 0x06};
    ARPPacket arp;


    int setSMAC(const char * sourcemac);
    int setTMAC(const char * targetmac);

    int setSIP(const char * srcIP);
    int setTIP(const char * trgIP);
    std::ostream& writeTo(std::ostream& os) const;
private:
    unsigned char * parseIP(const char * str);
    unsigned char * parseMAC(const char * str);
    size_t copyArray(const char * from, unsigned char * to, int len);

};

int sendPacket(const EthernetPacket * eth, const char * intrfc);

inline std::ostream& operator<<(std::ostream& os, const EthernetPacket eth){
    return eth.writeTo(os);
}

/* C-interface */
extern "C"{

}
#endif