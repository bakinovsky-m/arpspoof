#include "arppacket.h"

void EthernetPacket::setSMAC(const char * srcMAC){
    copyArray(srcMAC, arp.sourceHardwareAddress, arp.hardwareLength);
    copyArray(srcMAC, sourceMAC, arp.hardwareLength);
}

void EthernetPacket::setTMAC(const char * trgMAC){
    copyArray(trgMAC, arp.targetHardwareAddress, arp.hardwareLength);
    copyArray(trgMAC, targetMAC, arp.hardwareLength);
}

void EthernetPacket::setSIP(const char * srcIP){
    copyArray(srcIP, arp.sourceProtocolAddress, arp.protocolLength);
}

void EthernetPacket::setTIP(const char * trgIP){
    copyArray(trgIP, arp.targetProtocolAddress, arp.protocolLength);
}

void EthernetPacket::copyArray(const char * from, unsigned char * to, int len){
    unsigned char * fr = nullptr;
    if(len == arp.protocolLength){
        fr = parseIP(from);
    } else if(len == arp.hardwareLength){
        fr = parseMAC(from);
    } else {
        return;
    }
    for(std::ptrdiff_t i = 0; i < len; i += 1){
        to[i] = fr[i];
    }
    delete[] fr;
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

    if(sscanf(str, "%x:%x:%x:%x:%x:%x", &b[0], &b[1], &b[2], &b[3], &b[4], &b[5]) == 6){
        for(std::ptrdiff_t i = 0; i < 6; i += 1){
            res[i] = b[i];
        }
        
    }

    return res;
}

std::ostream& EthernetPacket::writeTo(std::ostream& os) const {
    std::string str = "";

    os << "source mac: ";
    for (std::ptrdiff_t i = 0 ; i < arp.hardwareLength; i++){
        os << std::to_string(sourceMAC[i]);
        os << ":";
    }
    os << "\b \n";

    os << "target mac: ";
    for (std::ptrdiff_t i = 0; i < arp.hardwareLength; i++){
        os << std::to_string(targetMAC[i]);
        os << ":";
    }
    os << "\b \n";

    os << "source ip: ";
    for (std::ptrdiff_t i = 0 ; i < arp.protocolLength; i++){
        os << std::to_string(arp.sourceProtocolAddress[i]);
        os << ".";
    }
    os << "\b \n";

    os << "target ip: ";
    for (std::ptrdiff_t i = 0 ; i < arp.protocolLength; i++){
        os << std::to_string(arp.targetProtocolAddress[i]);
        os << ".";
    }
    os << "\b \b";

    return os;
}

/* must be root */
int sendPacket(const EthernetPacket * eth, const char * intrfc){
    int s = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if(s < 0){
        throw "bad file descriptor";
        return -1;
    }

    sockaddr_ll socket_address;
    // address family, AF_PACKET for raw packet
    socket_address.sll_family = AF_PACKET;
    // index of the network device
    socket_address.sll_ifindex = if_nametoindex(intrfc);
    // address length
    socket_address.sll_halen = ETH_ALEN;
    // destination MAC
    for (size_t i = 0; i < eth->arp.hardwareLength; i += 1){
        socket_address.sll_addr[i] = eth->arp.targetHardwareAddress[i];
    }

    /*  
        second arg of sendto casts to char* because of windows needs
        linux don't give a fuck, as i see
        in manual it needs void*, but no errors appears at compiling
        magic
    */
    int ss = sendto(s, (char*)eth, sizeof(*eth), 0, (sockaddr*)&socket_address, sizeof(socket_address));
    std::cout << "Send return: " << ss << std::endl;
    std::cout << strerror(errno) << std::endl;
    if(ss < 0){
        throw "no data sent";
        return -1;
    }
    close(s);
    return 0;
}