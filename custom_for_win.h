#ifndef HG_CUSTOM_FOR_WIN_H
#define HG_CUSTOM_FOR_WIN_H

#include "netioapi.h"

#define AF_PACKET       17              /* Packet family                */
#define ETH_P_ARP       0x0806          /* Address Resolution packet    */
#define ETH_ALEN        6               /* Octets in one ethernet addr   */

typedef unsigned short __u16;
typedef __u16 __be16;

struct sockaddr_ll {
     unsigned short  sll_family;
     __be16          sll_protocol;
     int             sll_ifindex;
     unsigned short  sll_hatype;
     unsigned char   sll_pkttype;
     unsigned char   sll_halen;
     unsigned char   sll_addr[8];
};

#endif