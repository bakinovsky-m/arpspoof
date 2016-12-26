#ifndef HG_ETHPACKET_H
#define HG_ETHPACKET_H

// #include <string>
// #include <sstream> /* istringstream */
// // #include <iostream> /* cout's */
// #include <cstdio> /* sscanf() */
// // #include <cstring>

// cross platform?
#if defined _WIN32 || defined __WIN64 || defined __MINGW32__ || defined __MINGW64__ || defined __CYGWIN__ || defined __WINDOWS__

#include <winsock2.h>
#include <ws2tcpip.h>
#include "custom_for_win.h" /* my custom header with some definitions */

#include <stdint.h>
 
typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;

#else

#include <sys/socket.h> /* nothing needs this header */
#include <linux/if_packet.h> /* sockaddr_ll */
#include <linux/if_ether.h> /* ETH_P_ARP, ETH_ALEN */
#include <arpa/inet.h> /* htons() */
#include <net/if.h> /* if_nametoindex() */
#include <unistd.h> /* close() */

#endif


#ifdef _WINDOWS
#define LIB_CALL __cdecl
#else
#define LIB_CALL
#endif

#ifdef MY_DLL__EXPORTS
#define LIB_EXPORT __declspec(dllexport)
#else
#define LIB_EXPORT
#endif

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
#define ETHER_TYPE_FOR_ARP 0x0806
struct ARPPacket{
    uint16_t hardware;
    uint16_t protocol;
    uint8_t hardwareLength;
    uint8_t protocolLength ;

    uint16_t operationCode; //response

    uint8_t sourceHardwareAddress[6];
    uint8_t sourceProtocolAddress[4];
    uint8_t targetHardwareAddress[6];
    uint8_t targetProtocolAddress[4];
};

/**
    Ethernet frame:
        destination MAC 6 bytes
        source MAC 6 bytes
        type 2 bytes
        
        everything
**/

struct EthPacket{
    uint8_t targetMAC[6];
    uint8_t sourceMAC[6];
    uint8_t type[2];
    struct ARPPacket arp;
};

#ifdef __cplusplus
extern "C"{
#endif
    
    LIB_EXPORT int LIB_CALL cSendPacket(const struct EthPacket*, char*);
#ifdef __cplusplus
}
#endif

#endif