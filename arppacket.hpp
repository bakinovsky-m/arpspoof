#ifndef HG_ETHPACKET_HPP
#define HG_ETHPACKET_HPP

#include "arppacket.h"

#include <string>
#include <sstream>
#include <cstdio>

class EthernetPacket : public EthPacket{
public:
    EthernetPacket();
    EthernetPacket(const std::string& sourceMAC, const std::string& targetMAC, 
        const std::string& srcIP, const std::string& trgIP);

    std::ostream& writeTo(std::ostream& os) const;
private:
    void init();
    int setSMAC(const std::string& sourcemac);
    int setTMAC(const std::string& targetmac);
    int setSIP(const std::string& srcIP);
    int setTIP(const std::string& trgIP);
    uint8_t * parseIP(const std::string& str);
    uint8_t * parseMAC(const std::string& str);
    size_t copyArray(const std::string& from, uint8_t * to, int len);
};

int sendPacket(const EthernetPacket * eth, const std::string& intrfc);

inline std::ostream& operator<<(std::ostream& os, const EthernetPacket eth){
    return eth.writeTo(os);
}

#endif