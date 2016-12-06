#include "arppacket.h"

void EthernetPacket::setSMAC(const char * srcMAC){
    unsigned char * srcmac = parseMAC(srcMAC);
    for(std::ptrdiff_t it = 0; it < arp.hardwareLength; it += 1){
        sourceMAC[it] = srcmac[it];
        arp.sourceHardwareAddress[it] = srcmac[it];
    }
    delete[] srcmac;
}

void EthernetPacket::setTMAC(const char * trgMAC){
    unsigned char * trgmac = parseMAC(trgMAC);
    for(std::ptrdiff_t it = 0; it < arp.hardwareLength; it += 1){
        targetMAC[it] = trgmac[it];
        arp.targetHardwareAddress[it] = trgmac[it];
    }
    delete[] trgmac;
}

void EthernetPacket::setSIP(const char * srcIP){
    unsigned char * srcip = parseIP(srcIP);
    for (std::ptrdiff_t it = 0; it < arp.protocolLength; it += 1){
        arp.sourceProtocolAddress[it] = srcip[it];
    }   
    delete[] srcip;
}

void EthernetPacket::setTIP(const char * trgIP){
    unsigned char * trgip = parseIP(trgIP);
    for (std::ptrdiff_t it = 0; it < arp.protocolLength; it += 1){
        arp.targetProtocolAddress[it] = trgip[it];
    }   
    delete[] trgip;
}

unsigned char * EthernetPacket::parseIP(const char * str){
    int b[4]{0};
    char dot;
    unsigned char * res = new unsigned char[4]{0};
    std::istringstream s(str);

    s >> b[0] >> dot >> b[1] >> dot >> b[2] >> dot >> b[3];
    for(std::ptrdiff_t i = 0; i < 4; i += 1){
        res[i] = b[i];
    }
    return res;
}

unsigned char * EthernetPacket::parseMAC(const char * str){
    int b[6]{0};
    unsigned char * res = new unsigned char[6]{0};

    if(sscanf(str, "%x:%x:%x:%x:%x:%x", &b[0], &b[1], &b[2],
        &b[3], &b[4], &b[5]) == 6){
        for(std::ptrdiff_t i = 0; i < 6; i += 1){
            res[i] = b[i];
        }
        
    }

    return res;
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

/* must be root */
int sendPacket(const EthernetPacket * eth, const char * interface){
    int s = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if(s < 0){
        throw "bad file descriptor";
        return -1;
    }

    sockaddr_ll socket_address;
    // address family, AF_PACKET for raw packet
    socket_address.sll_family = AF_PACKET;
    // index of the network device
    socket_address.sll_ifindex = if_nametoindex(interface);
    // address length
    socket_address.sll_halen = ETH_ALEN;
    // destination MAC
    for (size_t i = 0; i < eth->arp.hardwareLength; i += 1){
        socket_address.sll_addr[i] = eth->arp.targetHardwareAddress[i];
    }

    int ss = sendto(s, (void*)eth, sizeof(*eth), 0,
    // sendto(s, (void*)eth, sizeof(*eth), 0,
        (sockaddr*)&socket_address, sizeof(socket_address));
    // std::cout << "Send return: " << ss << std::endl;
    // std::cout << strerror(errno) << std::endl;
    if(ss < 0){
        throw "no data sent";
        return -1;
    }
    close(s);
    return 0;
}