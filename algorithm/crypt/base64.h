#ifndef BASE64_H
#define BASE64_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/* B64 Interface for zero terminated Byte Strings. */
#define B64ENC(str) do { b64encode(str, strlen(str), true) } while(0)
#define B64DEC(str) do { b64decode(str, strlen(str), true) } while(0)

/* B64 Interface for zero terminated Byte Strings without padding(WOP). */
#define B64ENC_WOP(str) do { b64encode(str, strlen(str), false) } while(0)
#define B64DEC_WOP(str) do { b64decode(str, strlen(str), false) } while(0)

/*  
    Compute the max. Amount of needed Bytes for b64 Encoding. 
    Useful for examining Size of own Target Encoding Buffer.
*/
uint32_t b64maxLenEnc(uint32_t numBytes);
uint32_t b64maxLenEncStr(const unsigned char* bytes);

/*  
    Compute the max. Amount of needed Bytes for b64 Decoding. 
    Useful for examining Size of own Target Decoding Buffer.
*/
uint32_t b64maxLenDec(uint32_t numB64Bytes);
uint32_t b64maxLenDecStr(const unsigned char* b64Bytes);

/*
    Computes Base 64 encoding for a byte String and returns result.
    Result must be free'd by Caller.
*/
uint8_t* b64encode(uint8_t* bytes, size_t numBytes, bool padding);
/*
    Computes Base 64 decoding for a Base64 String and returns result.
    Result must be free'd by Caller.
*/
uint8_t* b64decode(uint8_t* bytes, size_t numBytes, bool padding);

/*
    Computes Base 64 encoding for a byte String and stores the Result into targebuffer.
    TargetBuffer must be large enough (see: b64maxLenEnc, b64maxLenEncStr).
*/
void b64encodeBuf(uint8_t* bytes, size_t numBytes, uint8_t* targetBuffer, uint32_t targetBufLen, bool padding);

/*
    Computes Base 64 decoding for a byte String and stores the Result into targebuffer.
    TargetBuffer must be large enough (see: b64maxLenDec, b64maxLenDecStr).
*/
void b64decodeBuf(uint8_t* bytes, size_t numBytes, uint8_t* targetBuffer, uint32_t targetBufLen, bool padding);

#endif