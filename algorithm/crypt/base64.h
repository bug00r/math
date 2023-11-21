#ifndef BASE64_H
#define BASE64_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

uint8_t* b64encode(uint8_t* bytes, size_t numBytes, bool padding);
uint8_t* b64decode(uint8_t* bytes, size_t numBytes, bool padding);

#endif