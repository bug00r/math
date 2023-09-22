#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

uint32_t crc32_u8(uint8_t* bytes, size_t numBytes);
uint32_t crc32_uc(unsigned char* bytes, size_t numBytes);

#endif