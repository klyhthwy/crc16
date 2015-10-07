#ifndef CRC16_HPP_
#define CRC16_HPP_

#include <stdint.h>

class crc16
{
    public:
        crc16(uint16_t seed);
        void process_byte(uint8_t data);
        void process_bytes(uint8_t *data, uint32_t size);
        uint16_t checksum(void);
        uint16_t reset(void);

    private:
        static const uint16_t CRC_TABLE_SIZE = 256;
        static const uint16_t CRC_TABLE[CRC_TABLE_SIZE];

        uint16_t seed_;
        uint16_t crc_;
};

#endif//CRC16_HPP_
