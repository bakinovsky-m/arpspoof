#include <cstdint>

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
struct ARPPacket{
    uint16_t hardware = 0x0001;
    uint16_t protocol = 0x0800;
    uint8_t hardwareLength = 6;
    uint8_t protocolLength = 4;

    uint16_t operationCode = 1;

    uint8_t sourceHardwareAddress[6]; // random?
    uint8_t sourceProtocolAddress[4]; // random?
    uint8_t targetHardwareAddress[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff}; // broadcast response, so MAC is FF:FF:FF:FF:FF:FF
    uint8_t targetProtocolAddress[4];

    void setTargetHwAddr(const uint8_t * hwaddr);
};