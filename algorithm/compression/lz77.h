#ifndef LZ77_H
#define LZ77_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct __lz77_buff 
{
    uint8_t*    bytes;
    size_t      numBytes;
} lz77_buf_t,*lz77BufPtr;

typedef struct __lz77_param 
{
    uint16_t    searchBufSize;
    uint16_t    lookaheadBufSize;
} lz77_param_t,*lz77ParamPtr;

typedef enum __lz77_return_codes {
    LZ77_OK = 0,
    LZ77_ERR
} lz77_result_t;


lz77_result_t en_lz77_u8(lz77BufPtr srcBuf, lz77BufPtr* dstBuf, lz77ParamPtr param);
lz77_result_t de_lz77_u8(lz77BufPtr srcBuf, lz77BufPtr* dstBuf);

#endif