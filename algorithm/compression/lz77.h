#ifndef LZ77_H
#define LZ77_H

#if defined(debug) && debug != 0
#include <stdio.h>
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct __lz77_buff 
{
    uint8_t*    bytes;
    size_t      numBytes;
} LZ77Buf,*lz77BufPtr;

typedef struct __lz77_param 
{
    uint16_t    searchBufSize;
    uint16_t    lookaheadBufSize;
} LZ77Param,*lz77ParamPtr;

typedef enum __lz77_return_codes {
    LZ77_OK = 0,
    LZ77_ERR
} LZ77Result;


LZ77Result en_lz77_u8(lz77BufPtr srcBuf, lz77BufPtr dstBuf, lz77ParamPtr param);
LZ77Result de_lz77_u8(lz77BufPtr srcBuf, lz77BufPtr dstBuf);

size_t lz77_get_dst_buf_size(lz77BufPtr srcBuf);

//TODO for external memory mgmt there could be a callback registration for handling en- and decoded chars

#endif