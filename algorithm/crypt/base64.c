#include "base64.h"

#define OCTECT_CNT_COMPLETE 3

static const char* b64Dict = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

typedef struct __b64_extract 
{
    uint8_t rest;
    uint8_t restMask;
    uint8_t cur;
    uint8_t curMask;
} b64ext_t;

static const b64ext_t extracts[] = { {0,0,6,252}, {2,3,4,240}, {4,15,2,192}, {6,0,6,63} };

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
    return (numB64Bytes * OCTECT_CNT_COMPLETE) / 4;
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

void b64encodeBuf(uint8_t* _bytes, size_t _numBytes, uint8_t* _targetBuffer, size_t _targetBufLen, bool padding)
{

    size_t numBytes = _numBytes, targetBufferIdx = 0, targetBufLen = _targetBufLen; 
    uint8_t *targetBuffer = _targetBuffer, *bytes = _bytes, 
            lastByte = 0, curByte = 0, octetCnt = 0, b64Idx = 0;

    const b64ext_t *curExtract = NULL, *nextExtract = NULL;

    /* targetbuffer not large enough. */
    if ( b64maxLenEnc(numBytes) > targetBufLen ) return;

    for(size_t curByteIdx = 0; curByteIdx < numBytes; ++curByteIdx, lastByte = curByte)
    {
        curByte = bytes[curByteIdx];

        curExtract = &extracts[targetBufferIdx % 4];
        nextExtract = curExtract + 1;

        b64Idx = (((lastByte & curExtract->restMask) << curExtract->cur) |
                 ( curByte & curExtract->curMask) >> nextExtract->rest );

        targetBuffer[targetBufferIdx++] = b64Dict[b64Idx]; 

        if (++octetCnt == OCTECT_CNT_COMPLETE) /* if 3 Byte full */
        {
            targetBuffer[targetBufferIdx++] = b64Dict[ curByte & nextExtract->curMask ];
            octetCnt = 0;
        }
        
    }

    if ( octetCnt != 0 )
    {
        uint8_t cntPadding = OCTECT_CNT_COMPLETE - octetCnt; 

        uint8_t mask = ( cntPadding == 1 ? 0xF : 0x3 ); /* 1 pad = 00001111 and 2 pad = 00000011 MASK */
        b64Idx = ( curByte & mask ) << (cntPadding << 1); /* moving */
        
        targetBuffer[targetBufferIdx++] = b64Dict[b64Idx];

        char paddingChar = ( padding ? '=' : '\0');

        switch(cntPadding)
        {
            case 1: targetBuffer[targetBufferIdx++] = paddingChar; break;
            case 2: targetBuffer[targetBufferIdx++] = paddingChar; 
                    targetBuffer[targetBufferIdx++] = paddingChar; break;
        }
        
    } 

}

void b64decodeBuf(uint8_t* _bytes, size_t _numBytes, uint8_t* _targetBuffer, size_t _targetBufLen, bool padding)
{

}