#include "arppacket.h"

int  EthernetPacket::setSMAC(const std::string srcMAC){
    size_t res1 = copyArray(srcMAC, arp.sourceHardwareAddress, arp.hardwareLength);
    size_t res2 = copyArray(srcMAC, sourceMAC, arp.hardwareLength);
    if(res1 != arp.hardwareLength || res2 != arp.hardwareLength){
        return -1;
    }
    return 0;
}

int EthernetPacket::setTMAC(const std::string trgMAC){
    size_t res1 = copyArray(trgMAC, arp.targetHardwareAddress, arp.hardwareLength);
    size_t res2 = copyArray(trgMAC, targetMAC, arp.hardwareLength);
    if(res1 != arp.hardwareLength || res2 != arp.hardwareLength){
        return -1;
    }
    return 0;
}

int EthernetPacket::setSIP(const std::string srcIP){
    size_t res = copyArray(srcIP, arp.sourceProtocolAddress, arp.protocolLength);
    if (res != arp.protocolLength){
        return -1;
    }
    return 0;
}

int EthernetPacket::setTIP(const std::string trgIP){
    size_t res = copyArray(trgIP, arp.targetProtocolAddress, arp.protocolLength);
    if (res != arp.protocolLength){
        return -1;
    }
    return 0;
}

/* 
    return: count of copied bytes or -1 in case of wrong length
*/
size_t EthernetPacket::copyArray(const std::string from, unsigned char * to, int len){
    unsigned char * fr = nullptr;
    if(len == arp.protocolLength){
        fr = parseIP(from);
    } else if(len == arp.hardwareLength){
        fr = parseMAC(from);
    } else {
        return -1;
    }

    size_t it = 0;
    for(std::ptrdiff_t i = 0; i < len; i += 1){
        to[i] = fr[i];
        it++;
    }
    delete[] fr;

    return it;
}

unsigned char * EthernetPacket::parseIP(const std::string str){
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

unsigned char * EthernetPacket::parseMAC(const std::string str){
    int b[6]{0};
    char dot;
    unsigned char * res = new unsigned char[6]{0};
    std::istringstream s(str);

    s >> std::hex >> b[0] >> dot >> b[1] >> dot >> b[2] >> dot >> b[3] >> dot >> b[4] >> dot >> b[5];
    for(std::ptrdiff_t i = 0; i < 6; i += 1){
        res[i] = b[i];
    }
    return res;
}

std::ostream& EthernetPacket::writeTo(std::ostream& os) const {
    std::string str = "";

    os << "source mac: ";
    for (std::ptrdiff_t i = 0 ; i < arp.hardwareLength; i++){
        os << std::hex << static_cast<int>(sourceMAC[i]);
        os << ":";
    }
    os << "\b \n";

    os << "target mac: ";
    for (std::ptrdiff_t i = 0; i < arp.hardwareLength; i++){
        os << std::hex << static_cast<int>(targetMAC[i]);
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
int sendPacket(const EthernetPacket * eth, const std::string intrfc){
    int s = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if(s < 0){
        throw "bad file descriptor";
        return -1;
    }

    sockaddr_ll socket_address;
    // address family, AF_PACKET for raw packet
    socket_address.sll_family = AF_PACKET;
    // index of the network device
    socket_address.sll_ifindex = if_nametoindex(intrfc.c_str());
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
    if(ss < 0){
        throw "no data sent";
        return -1;
    }
    close(s);
    return 0;
}

int cSendPacket(const EthPacket* eth, char* ifname){
    EthernetPacket ethpack = epStructToEpClass(eth);
    int res = sendPacket(&ethpack, std::string(ifname));
    return res;
}

EthernetPacket epStructToEpClass(const EthPacket* ep){
    EthernetPacket eth = EthernetPacket();
    std::memcpy(&eth, ep, sizeof(eth));
    return eth;
}