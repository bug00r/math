#include "base64.h"

static const char* b64Dict = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


uint32_t b64maxLenEnc(uint32_t numBytes)
{
    return (uint32_t)(ceilf( (float)numBytes / 3.0 ) * 4);
}

uint32_t b64maxLenEncStr(const unsigned char* bytes)
{
    return b64maxLenEnc(strlen((const char*)bytes));
}

uint32_t b64maxLenDec(uint32_t numB64Bytes)
{
    return (numB64Bytes * 3) / 4;
}

uint32_t b64maxLenDecStr(const unsigned char* b64Bytes)
{
    return b64maxLenDec(strlen((const char*)b64Bytes));
}

uint8_t* b64encode(uint8_t* bytes, size_t numBytes, bool padding)
{   
    uint32_t bufLen = b64maxLenEnc(numBytes);
    uint8_t *buffer = malloc( sizeof(uint8_t) * bufLen);
    
    b64encodeBuf(bytes, numBytes, buffer, padding);

    return buffer;
}   

uint8_t* b64decode(uint8_t* bytes, size_t numBytes, bool padding)
{
    uint32_t bufLen = b64maxLenDec(numBytes);
    uint8_t *buffer = malloc( sizeof(uint8_t) * bufLen);
    
    b64encodeBuf(bytes, numBytes, buffer, padding);

    return buffer;
}

void b64encodeBuf(uint8_t* bytes, size_t numBytes, uint8_t* targetBuffer, bool padding)
{

}

void b64decodeBuf(uint8_t* bytes, size_t numBytes, uint8_t* targetBuffer, bool padding)
{

}