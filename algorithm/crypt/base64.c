#include "base64.h"

#define OCTECT_CNT_COMPLETE 3

static const char* lookupTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

#define _ 255

static const uint8_t reverseLookupTable[] = 
{ _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
  _,_,_,62,_,_,_,63,52,53,54,55,56,57,58,59,60,61,_,_,_,_,_,_,_,0,1,2,3,4,5,6,7,8,
  9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,_,_,_,_,_,_,26,27,28,29,30,31,
  32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51
};

#undef _

typedef struct __b64_extract 
{
    uint8_t rest;
    uint8_t restMask;
    uint8_t cur;
    uint8_t curMask;
} b64ext_t;

static const b64ext_t extracts[] = { {0,0,6,252}, {2,3,4,240}, {4,15,2,192}, {6,0,6,63} };
static const b64ext_t extractsDecode[] = { {0,0,6,63}, {2,48,4,15}, {4,60,2,3}, {6,63,0,63} };

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

uint8_t* b64decode(uint8_t* bytes, size_t numBytes)
{
    uint32_t bufLen = b64maxLenDec(numBytes);
    uint8_t *buffer = malloc( sizeof(uint8_t) * (bufLen + 1)) ;
    
    b64decodeBuf(bytes, numBytes, buffer, bufLen);

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

        targetBuffer[targetBufferIdx++] = lookupTable[b64Idx]; 

        if (++octetCnt == OCTECT_CNT_COMPLETE) /* if 3 Byte full */
        {
            targetBuffer[targetBufferIdx++] = lookupTable[ curByte & nextExtract->curMask ];
            octetCnt = 0;
        }
        
    }

    if ( octetCnt != 0 )
    {
        uint8_t cntPadding = OCTECT_CNT_COMPLETE - octetCnt; 

        uint8_t mask = ( cntPadding == 1 ? 0xF : 0x3 ); /* 1 pad = 00001111 and 2 pad = 00000011 MASK */
        b64Idx = ( curByte & mask ) << (cntPadding << 1); /* moving */
        
        targetBuffer[targetBufferIdx++] = lookupTable[b64Idx];

        char paddingChar = ( padding ? '=' : '\0');

        switch(cntPadding)
        {
            case 1: targetBuffer[targetBufferIdx++] = paddingChar; break;
            case 2: targetBuffer[targetBufferIdx++] = paddingChar; 
                    targetBuffer[targetBufferIdx++] = paddingChar; break;
        }
        
    } 

}

void b64decodeBuf(uint8_t* _bytes, size_t _numBytes, uint8_t* _targetBuffer, size_t _targetBufLen)
{

    size_t numBytes = _numBytes, targetBufferIdx = 0, targetBufLen = _targetBufLen; 
    uint8_t *targetBuffer = _targetBuffer, *bytes = _bytes, 
            curB64Byte = 0, cntOctet = 0, lastRevIdx = 0, revIdx = 0;

    const b64ext_t *curExtract = NULL, *lastExtract = &extractsDecode[3];

    /* targetbuffer not large enough. */
    if ( b64maxLenDec(numBytes) > targetBufLen ) return;

    for(size_t curByteIdx = 0; curByteIdx < numBytes; ++curByteIdx, lastRevIdx = revIdx, lastExtract = curExtract)
    {

        curExtract = &extractsDecode[curByteIdx % 4];

        curB64Byte = bytes[curByteIdx];
        revIdx = reverseLookupTable[curB64Byte];

        bool paddingReached = (curB64Byte == '=');

        uint8_t curDecodeByte = ((lastRevIdx & lastExtract->curMask) << curExtract->rest) |
                                ( paddingReached ? 0 : (revIdx & curExtract->restMask) >> curExtract->cur );

        if ( curDecodeByte )
        {
            targetBuffer[targetBufferIdx++] = curDecodeByte;

            if (++cntOctet == OCTECT_CNT_COMPLETE)
            {
                cntOctet = 0;
                revIdx = 0;
            }
        }
    
        if ( paddingReached ) break;
    }
    
    uint8_t cntPadding = OCTECT_CNT_COMPLETE - cntOctet;

    if ( cntPadding )
    {
        targetBuffer[targetBufferIdx++] = ((lastRevIdx & lastExtract->curMask) << curExtract->rest);
        targetBuffer[targetBufferIdx] = '\0';
    }

}