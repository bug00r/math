#include "checksum.h"

/* Generator Polynom */
#define CRC32MASKREV 0xEDB88320
#define BITS 8

uint32_t crc32_u8(uint8_t* _bytes, size_t _numBytes)
{
    uint32_t checksum = ~0;
    size_t numBytes = _numBytes;
    uint8_t* bytes =_bytes;

    for (size_t curByte = 0; curByte < numBytes; curByte++)
    {
        checksum ^= bytes[curByte];
        for (int j = 0; j < BITS; j++) {
            checksum = (checksum >> 1) ^ ((checksum & 1) ? CRC32MASKREV : 0);
        }
    }

    return checksum ^ ~0;
}

uint32_t crc32_uc(unsigned char* bytes, size_t numBytes)
{
    return crc32_u8((uint8_t*)bytes, numBytes);
}
