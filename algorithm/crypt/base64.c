#include "base64.h"

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
    uint8_t *buffer = malloc( sizeof(uint8_t) * (bufLen + 1));
    
    b64encodeBuf(bytes, numBytes, buffer, bufLen, padding);

    buffer[bufLen] = '\0';

    return buffer;
}   

uint8_t* b64decode(uint8_t* bytes, size_t numBytes, bool padding)
{
    uint32_t bufLen = b64maxLenDec(numBytes);
    uint8_t *buffer = malloc( sizeof(uint8_t) * (bufLen + 1)) ;
    
    b64decodeBuf(bytes, numBytes, buffer, bufLen, padding);

    buffer[bufLen] = '\0';

    return buffer;
}

static const char* b64Dict = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

typedef struct __b64_extract 
{
    uint8_t rest;
    uint8_t restMask;
    uint8_t cur;
    uint8_t curMask;
} b64ext_t;

static const b64ext_t extracts[] = { {0,0,6,252}, {2,3,4,240}, {4,15,2,192}, {6,0,6,63} };

void b64encodeBuf(uint8_t* _bytes, size_t numBytes, uint8_t* targetBuffer, uint32_t targetBufLen, bool padding)
{

    uint8_t* bytes = _bytes;

    uint8_t lastByte = 0;
    uint8_t curByte = 0;
    const b64ext_t *curExtract = NULL, *nextExtract = NULL;
    uint32_t targetBufferIdx = 0;
    uint8_t octetCnt = 0;
    for(size_t curByteIdx = 0; curByteIdx < numBytes; ++curByteIdx)
    {
        curByte = bytes[curByteIdx];

        curExtract = &extracts[targetBufferIdx % 4];
        nextExtract = &extracts[(targetBufferIdx + 1) % 4];

        uint8_t b64Idx = ((lastByte & curExtract->restMask) << curExtract->cur) |
                         ( curByte & curExtract->curMask) >> nextExtract->rest;

        targetBuffer[targetBufferIdx++] = b64Dict[b64Idx % 64]; /* 64 secure overflow */

        octetCnt++;

        if (octetCnt == 3) /* if 3 Byte full */
        {
            b64Idx = ( curByte & nextExtract->curMask);
            targetBuffer[targetBufferIdx++] = b64Dict[b64Idx % 64]; /* 64 secure overflow */
            octetCnt = 0;
        }

        lastByte = curByte;
    }

    uint8_t cntPadding = targetBufLen - targetBufferIdx - 1; 
    
    if ( cntPadding != 0 )
    {
        uint8_t mask = ( cntPadding == 1 ? 15 : 3 ); /* 1 pad = 00001111 and 2 pad = 00000011 MASK */
        uint8_t b64Idx = ( curByte & mask ) << (cntPadding * 2); /* moving */
        
        targetBuffer[targetBufferIdx++] = b64Dict[b64Idx % 64]; /* 64 secure overflow */

        switch(cntPadding)
        {
            case 1: targetBuffer[targetBufferIdx++] = '='; break;
            case 2: targetBuffer[targetBufferIdx++] = '='; 
                    targetBuffer[targetBufferIdx++] = '='; break;
        }

    } 

}

void b64decodeBuf(uint8_t* bytes, size_t numBytes, uint8_t* targetBuffer, uint32_t targetBufLen, bool padding)
{

}