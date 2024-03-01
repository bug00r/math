#include "lz77.h"

//max len of triplets based on one Nibble
static const uint32_t TR_MAX_LEN = 0xF;
static const uint32_t TR_MAXP1_LEN = 0x10;
#define _TRIPLET_SIZE 0x3
static const uint32_t TRIPLET_SIZE = _TRIPLET_SIZE;

/***** PRIVATE INTERFACE *****/
typedef struct __lz77_buf_pos
{
    uint8_t *start;
    uint8_t *end;
} lz77_buf_pos_t, *lz77BufPosPtr;

typedef struct __lz77_sliding_window 
{
    /* Search Buffer Positions */
    lz77_buf_pos_t sbBuf; 
    /* lookahed Buffer Positions */
    lz77_buf_pos_t laBuf;
} lz77_sliding_window_t, *lz77SlidingWindowPtr;

typedef struct __lz77_context
{
    /* current processing position */
    uint8_t *pos;
    /* current dump processing position */
    uint8_t *dstBufPos;
    /* sliding window, depends on current processing position */ 
    lz77_sliding_window_t slWin;
    /* Buffer with bytes to compress */
    lz77BufPtr  srcBuf; 
    /* End of srcBuffer */
    uint8_t *eofSrcBuf;
    /* Buffer with result bytes */
    lz77BufPtr  dstBuf;
    /* Definition of lz77 Parameter */ 
    lz77ParamPtr param;    
} lz77_ctx_t, *lz77CtxPtr;

static bool __lz77_search_buffer_available(lz77CtxPtr _ctx)
{
    lz77CtxPtr ctx = _ctx;
    lz77BufPosPtr searchBufPos = &ctx->slWin.sbBuf;

    return ( searchBufPos->start != NULL && searchBufPos->end != NULL );
}

static void __lz77_set_search_buffer(lz77CtxPtr _ctx)
{
    lz77CtxPtr ctx = _ctx;
    lz77BufPosPtr searchBufPos = &ctx->slWin.sbBuf;
    lz77BufPtr srcBuffer = ctx->srcBuf;

    uint8_t *startSrcBuf = &srcBuffer->bytes[0];

    uint16_t paramSBufSize = ctx->param->searchBufSize;
    size_t maxPossSBufSize = ctx->pos - startSrcBuf;

    /* search buffer available */
    if ( maxPossSBufSize )
    {
        uint16_t curSBufSize = ( maxPossSBufSize < paramSBufSize ? maxPossSBufSize : paramSBufSize );
        
        searchBufPos->start = ctx->pos - 1;
        searchBufPos->end = ctx->pos - curSBufSize;
    } 
    else
    {
        searchBufPos->start = NULL;
        searchBufPos->end = NULL;
    }        
}

/*static bool __lz77_lookahed_buffer_available(lz77CtxPtr _ctx)
{
    lz77CtxPtr ctx = _ctx;
    lz77BufPosPtr lookAheadBufPos = &ctx->slWin.laBuf;

    return ( lookAheadBufPos->start < lookAheadBufPos->end );
}*/

static void __lz77_set_lookahed_buffer(lz77CtxPtr _ctx)
{
    lz77CtxPtr ctx = _ctx;
    lz77BufPosPtr lookAheadBufPos = &ctx->slWin.laBuf;
    lz77BufPtr srcBuffer = ctx->srcBuf;

    uint8_t *endSrcBuf = &srcBuffer->bytes[0] + srcBuffer->numBytes;
    
    uint16_t paramLaBufSize = ctx->param->lookaheadBufSize;
    size_t maxPossLaBufSize = endSrcBuf - ctx->pos;

    #if defined(debug) && debug != 0
    printf("maxPossLaBufSize: %lli\n", maxPossLaBufSize);
    #endif

    int16_t curLaBufSize = ( maxPossLaBufSize < paramLaBufSize ? maxPossLaBufSize : paramLaBufSize );

    lookAheadBufPos->start = ctx->pos;
    lookAheadBufPos->end = ctx->pos + curLaBufSize;
}

/*static void __lz77_set_sliding_window(lz77CtxPtr _ctx)
{
    lz77CtxPtr ctx = _ctx;

    __lz77_set_search_buffer(ctx);
    __lz77_set_lookahed_buffer(ctx);
}*/

static void __lz77_init_dst_buf(lz77CtxPtr _ctx)
{
    lz77CtxPtr ctx = _ctx;

    //Destination Buffer will be cleared at Beginning
    ctx->dstBuf->bytes = NULL;
    ctx->dstBuf->numBytes = 0;
}

static void __lz77_init_ctx(lz77CtxPtr _ctx, lz77BufPtr srcBuf, lz77BufPtr dstBuf, lz77ParamPtr param)
{
    lz77CtxPtr ctx = _ctx;
    ctx->pos = &srcBuf->bytes[0]; 
    ctx->srcBuf = srcBuf;
    ctx->dstBuf = dstBuf;
    
    ctx->eofSrcBuf = ctx->pos + srcBuf->numBytes;

    __lz77_init_dst_buf(ctx);

    ctx->param = param;
}

/* currently not using bitfields because lib should be usable with c99 too*/
typedef struct __lz77_triplet 
{
    uint8_t bytes[_TRIPLET_SIZE];
} lz77_priplet_t,*lz77TripletPtr;

static void __lz77_dump_triplet_to_dst_buffer(lz77CtxPtr _ctx, lz77TripletPtr _curTriplet)
{
    lz77CtxPtr ctx = _ctx;
    lz77TripletPtr curTriplet = _curTriplet;
    
    lz77BufPtr dstBuf = ctx->dstBuf;

    if ( dstBuf->bytes == NULL )
    {
        size_t neededByteCnt = ctx->srcBuf->numBytes * 2;

        #if defined(debug) && debug != 0
        printf("dst Buf Size: %lli\n", sizeof(uint8_t) * neededByteCnt);
        #endif
        
        dstBuf->bytes = malloc(sizeof(uint8_t) * neededByteCnt);
        dstBuf->numBytes = neededByteCnt;
        ctx->dstBufPos = dstBuf->bytes; 
    }

    //TODO DUMPING
    *ctx->dstBufPos++ = curTriplet->bytes[0]; 
    *ctx->dstBufPos++ = curTriplet->bytes[1];
    *ctx->dstBufPos++ = curTriplet->bytes[2];
}

static void __lz77_pack_triplet(lz77TripletPtr _curTriplet,
                                uint32_t *_offset, uint32_t *_len, uint8_t *_chr)
{
    lz77TripletPtr curTriplet = _curTriplet;
    uint32_t offset = *_offset, len = *_len;
    uint8_t chr = *_chr;

    curTriplet->bytes[0] = 0 | ( len << 0x4 ) | (offset >> 0x8);
    curTriplet->bytes[1] = offset & 0xFF;
    curTriplet->bytes[2] = chr;

    #if defined(debug) && debug != 0
    printf("packed(l,o,c) => bytes: (%i,%i,%c) => (%x,%x,%c)\n",
            len,offset,chr, 
            curTriplet->bytes[0],curTriplet->bytes[1],curTriplet->bytes[2]);
    #endif

}

static void __lz77_pack_and_dump_byte_repeat_triplet(lz77CtxPtr _ctx, lz77TripletPtr _curTriplet,
                                uint32_t *_offset, uint32_t *_len, uint8_t *_chr)
{
    lz77CtxPtr ctx = _ctx;
    lz77TripletPtr curTriplet = _curTriplet;
    uint32_t len = *_len, offset = *_offset, maxLen = TR_MAX_LEN;
    uint8_t nextChr = *_chr, repeatChr = *(ctx->pos);

    #if defined(debug) && debug != 0
    printf("repeating single bytes: (%i,%i,%c) ... splitting into:\n",
            len,offset,nextChr);
    #endif
    

    while( len > TR_MAX_LEN)
    {
        len -= TR_MAXP1_LEN;  //reduce by max len

        __lz77_pack_triplet(curTriplet, &offset, &maxLen, &repeatChr);
        __lz77_dump_triplet_to_dst_buffer(ctx, curTriplet);
    }
    
    #if defined(debug) && debug != 0
    printf("-- packing rest --\n");
    #endif

    if ( len == 0 ) offset = 0;
    
    __lz77_pack_triplet(curTriplet, &offset, &len, &nextChr);
    __lz77_dump_triplet_to_dst_buffer(ctx, curTriplet);
    

}

static void __lz77_pack_and_dump_bytes_repeat_triplet(lz77CtxPtr _ctx, lz77TripletPtr _curTriplet,
                                uint32_t *_offset, uint32_t *_len, uint8_t *_chr)
{
    lz77CtxPtr ctx = _ctx;
    lz77TripletPtr curTriplet = _curTriplet;
    uint32_t len = *_len, offset = *_offset, maxLen = TR_MAX_LEN;
    uint8_t nextChr = *_chr;

    #if defined(debug) && debug != 0
    printf("repeating multiple bytes: (%i,%i,%c) ... splitting into:\n",
            len,offset,nextChr);
    #endif

    uint8_t *lastPos = ctx->pos - offset;

    #if defined(debug) && debug != 0
    printf("last pos byte: %c \n",*lastPos);
    #endif

    size_t cntFullTriplets = (int)((float)len / (float)(TR_MAX_LEN + 1));
    size_t curTriplets = 0;

    uint32_t curOffset = 0;
    while( curTriplets < cntFullTriplets)
    {
        len -= TR_MAXP1_LEN;

        lastPos += TR_MAX_LEN;

        curOffset = ( curTriplets == 0 ? offset : (TR_MAX_LEN < offset ? offset : TR_MAX_LEN));

        #if defined(debug) && debug != 0
        printf("offset of \"%c\" =  %i \n",*lastPos, curOffset);
        #endif

        __lz77_pack_triplet(curTriplet, &curOffset, &maxLen, lastPos++);
        __lz77_dump_triplet_to_dst_buffer(ctx, curTriplet);

        curTriplets++;
    }
    
    #if defined(debug) && debug != 0
    printf("-- packing rest --\n");
    #endif

    curOffset = ( curTriplets == 0 ? offset : (TR_MAX_LEN < offset ? offset : TR_MAX_LEN));

    __lz77_pack_triplet(curTriplet, &curOffset, &len, &nextChr);
    __lz77_dump_triplet_to_dst_buffer(ctx, curTriplet);

}

static void __lz77_pack_and_dump_overflow_triplet(lz77CtxPtr _ctx, lz77TripletPtr _curTriplet,
                                uint32_t *_offset, uint32_t *_len, uint8_t *_chr)
{
    lz77CtxPtr ctx = _ctx;
    lz77TripletPtr curTriplet = _curTriplet;
    uint32_t len = *_len, offset = *_offset, usedOffset = *_offset;
    uint8_t nextChr = *_chr;

    #if defined(debug) && debug != 0
    printf("normal triplet overflow: (%i,%i,%c) ... splitting into:\n",
            len,offset,nextChr);
    #endif
    /*
        ine Quadraturamplitudenmodulation e && ine Quadraturamplitudenmodulation b

        splitting: "ine Quadraturamplitudenmodulation " (34,40,b)

        "ine Quadraturamp"      (15,40,p)       //für das komplette Start triplet l=15,o=Base Offset,c=ctxPos-(offset-15)  
        "litudenmodulation "    (15,24,o)       //für jedes weitere triplet wird l=15, o= offset-=16,c=ctxPos-(offset-15)
        "n "                    (1,8,' ')       //für das letzte Triplet gilt: l=restlen-1, o= offset-=16, c=ctxPos-1

    */

    size_t completeTriplets = (int)((float)len / (float)TR_MAXP1_LEN);
    size_t curCompleteTriplet = 0;

    while(curCompleteTriplet++ < completeTriplets)
    {
    
        __lz77_pack_triplet(curTriplet, &offset, (uint32_t*)&TR_MAX_LEN, ctx->pos-usedOffset+TR_MAX_LEN);
        __lz77_dump_triplet_to_dst_buffer(ctx, curTriplet);

        usedOffset -= TR_MAXP1_LEN;
        len -= TR_MAXP1_LEN;
    }

    #if defined(debug) && debug != 0
    printf("-- packing rest --\n");
    #endif

    if ( len == 0 ) offset = 0;
    
    __lz77_pack_triplet(curTriplet, &offset, &len, &nextChr);
    __lz77_dump_triplet_to_dst_buffer(ctx, curTriplet);

}

static void __lz77_pack_and_dump_triplet(lz77CtxPtr _ctx, lz77TripletPtr _curTriplet,
                                uint32_t *_offset, uint32_t *_len, uint8_t *_chr)
{
    //The CTX will be need to implement RLE and Repeat and very long results(must be split because of the limit of len by 15(4bit))
    lz77CtxPtr ctx = _ctx;
    lz77TripletPtr curTriplet = _curTriplet;
    uint32_t len = *_len, offset = *_offset;

    if ( len > TR_MAX_LEN )
    {
        if ( offset == 1 )
        {
            __lz77_pack_and_dump_byte_repeat_triplet(ctx, curTriplet, _offset, _len, _chr);
        }
        else if ( len > offset )
        {
            __lz77_pack_and_dump_bytes_repeat_triplet(ctx, curTriplet, _offset, _len, _chr);
        }
        else 
        {
            __lz77_pack_and_dump_overflow_triplet(ctx, curTriplet, _offset, _len, _chr);
        }
    }
    else
    {
        __lz77_pack_triplet(curTriplet, _offset, _len, _chr);
        __lz77_dump_triplet_to_dst_buffer(ctx, curTriplet);
    }

} 

#if defined(debug) && debug != 0

static void __lz77_printf_string(uint8_t *_strStart, uint8_t *_strEnd)
{
    uint8_t *curChar = _strStart, *strEnd = _strEnd;
    while (curChar <= strEnd) printf("%c", *curChar++);
}

static void __lz77_cmp_dgb_print(uint8_t *_sbufStart, uint8_t *_sbufEnd,
                                 uint8_t *_laBufStart, uint8_t *_lsBufEnd)
{   
    uint8_t *sbufStart = _sbufStart, *sbufEnd = _sbufEnd,
            *laBufStart = _laBufStart, *lsBufEnd = _lsBufEnd;
    __lz77_printf_string(sbufStart, sbufEnd);
    printf(" && ");
    __lz77_printf_string(laBufStart, lsBufEnd);
    printf("\n");
}
#endif


static void __lz77_search_triplet(lz77CtxPtr _ctx, 
                                  uint32_t *_offset, uint32_t *_len, uint8_t *_chr)
{
    lz77CtxPtr ctx = _ctx;
    lz77SlidingWindowPtr slWinPtr = &ctx->slWin;
    lz77BufPosPtr sbBufPtr = &slWinPtr->sbBuf;
    lz77BufPosPtr laBufPtr = &slWinPtr->laBuf;
    
    uint32_t *offset = _offset, *len = _len;
    uint8_t *chr = _chr, *curSBufStartPos = sbBufPtr->start;

    //Search Buffer Available?
    while ( curSBufStartPos >= sbBufPtr->end )
    {
        
        uint8_t *curSBufcmpPos = curSBufStartPos, *curlaBufcmpPos = laBufPtr->start; 
        bool match = true;

        //For Repeats and RLE we have to search until lookahed Buffer at least(Maybe until Buffer end)
        while ( curlaBufcmpPos <= laBufPtr->end )
        {
            #if defined(debug) && debug > 1
            __lz77_cmp_dgb_print(curSBufStartPos, curSBufcmpPos, laBufPtr->start, curlaBufcmpPos);
            #endif
            
            if ( *curSBufcmpPos != *curlaBufcmpPos ) 
            {
                break;
            } 
            else
            {
                match = true;
            }

            curSBufcmpPos++;
            curlaBufcmpPos++;
        }

        uint32_t curLen = curlaBufcmpPos - laBufPtr->start;

        //Found Something and result is larger than a match before
        if (match && curLen > *len)
        {
            *offset = ctx->pos - curSBufStartPos;
            *len = curlaBufcmpPos - laBufPtr->start;
            *chr = *curlaBufcmpPos;
            
            // If EOF Lookahead Buffer reached
            if ( curlaBufcmpPos == laBufPtr->end )
            {
                //reduce len because we need to add next char
                *len -= 1;
                //last char from one step ahead Lookahead Buffer compare Position
                *chr = *(curlaBufcmpPos - 1);
            }

            #if defined(debug) && debug != 0
            printf("o: %i, l: %i n: %c \n", *offset, *len, *chr);
            printf("cur la pos: %p eof src Buf: %p\n", curlaBufcmpPos, ctx->eofSrcBuf);
            #endif
            
            //Lookahead Compare Position reached EOF SRC Buffer. This can happen during RLE Search.
            if ( curlaBufcmpPos == ctx->eofSrcBuf )
            {
                #if defined(debug) && debug != 0
                printf("SRC BUFFER END REACHED...ABORT\n");
                #endif
                break;
            }
        }

        curSBufStartPos--;
    }

    if ( !*offset && !*len ) *chr = *(ctx->pos + *len );

}

static void __lz77_search_next_triplet(lz77CtxPtr _ctx, lz77TripletPtr _curTriplet)
{
    lz77CtxPtr ctx = _ctx;
    lz77TripletPtr curTriplet = _curTriplet;
    uint32_t offset = 0, len = 0;
    uint8_t chr = 0; 
    
    //TODO searching with every special situation
    //At first we will implement a very simple Version, this will be optimzed later
    if ( __lz77_search_buffer_available(ctx) )
    {
        __lz77_search_triplet(ctx, &offset, &len, &chr);
    }
    else
    {
        chr = *ctx->pos;
    }

    __lz77_pack_and_dump_triplet(ctx, curTriplet, &offset, &len, &chr);

    ctx->pos += len;
    ctx->pos++;

    #if defined(debug) && debug != 0
    printf("nxt Pos is: %c\n", *ctx->pos);
    #endif

}

static void __lz77_encode(lz77CtxPtr _ctx)
{
    lz77CtxPtr ctx = _ctx;
    lz77_priplet_t curTriplet;
    lz77TripletPtr curTripletPtr = &curTriplet;

    __lz77_set_lookahed_buffer(ctx);
    while ( ctx->pos < ctx->eofSrcBuf ) 
    {    
        __lz77_set_search_buffer(ctx);

        __lz77_search_next_triplet(ctx, curTripletPtr);

        __lz77_set_lookahed_buffer(ctx);
    } 
    
    ctx->dstBuf->numBytes = ctx->dstBufPos - &ctx->dstBuf->bytes[0];

}

bool __lz77_cnt_triplets_valid(lz77BufPtr srcBuf)
{
    return (srcBuf->numBytes % TRIPLET_SIZE) == 0;
}

bool __lz77_enc_src_buf_valid(lz77BufPtr srcBuf)
{
    return ( (srcBuf->bytes != NULL) && (srcBuf->numBytes > 2) && __lz77_cnt_triplets_valid(srcBuf));
}

size_t __lz77_calc_dst_buf_size(lz77BufPtr _srcBuf)
{
    lz77BufPtr srcBuf = _srcBuf;
    uint8_t *curLenBytePtr = srcBuf->bytes, *srcBufEndPtr = srcBuf->bytes + srcBuf->numBytes;
    size_t neededDstBufSize = 0;
    
    while ( curLenBytePtr < srcBufEndPtr )
    {
        #if defined(debug) && debug > 1
        printf("Add Len: %c = %i\n", *curLenBytePtr, *curLenBytePtr >> 0x4 );
        #endif 

        neededDstBufSize += ( *curLenBytePtr >> 0x4 );
        neededDstBufSize++;

        curLenBytePtr += TRIPLET_SIZE;
    }

    return neededDstBufSize;
}

void __lz77_calc_size_and_init_dst_buf(lz77CtxPtr _ctx)
{
    lz77CtxPtr ctx = _ctx;
    lz77BufPtr srcBuf = ctx->srcBuf, dstBuf = ctx->dstBuf;

    size_t neededDstBufSize = __lz77_calc_dst_buf_size(srcBuf);

    dstBuf->numBytes = neededDstBufSize;
    dstBuf->bytes = malloc( sizeof(uint8_t) * neededDstBufSize );

    ctx->dstBufPos = dstBuf->bytes;

    #if defined(debug) && debug != 0
    printf("Needed Dst Buf Size: %lli\n", dstBuf->numBytes);
    #endif

}

#if defined(debug) && debug > 1
void __lz77_print_cur_dst_buf(lz77CtxPtr _ctx)
{
    lz77CtxPtr ctx = _ctx;
    lz77BufPtr dstBuf = ctx->dstBuf;
    uint8_t *curDstBufPos = ctx->dstBufPos, *dstStartPos = dstBuf->bytes;
    
    printf("dstBuf: \"");
    while(dstStartPos != curDstBufPos)
    {
        printf("%c", *dstStartPos);
        dstStartPos++;
    }
    printf("\n");

}
#endif

void __lz77_extend_dst_buf(lz77CtxPtr _ctx, uint32_t *_len, uint32_t *_offset, uint8_t *_nextChr)
{
    lz77CtxPtr ctx = _ctx;
    uint32_t len = *_len, offset = *_offset;
    uint8_t nextChr = *_nextChr;
    
    bool needLen = true;

    //add new Character to buffer
    if ( len == 0 )
    {
        *ctx->dstBufPos = nextChr;
    }
    //Repeating
    else if ( len > offset )
    {
        //Repeat single bytes (RLE)
        if ( offset == 1 )
        {
            memset(ctx->dstBufPos, *(ctx->dstBufPos - offset), len);
        }
        //Repeat multiple bytes
        else
        {
            size_t completeRepeats = (int)((float)len / (float)offset);
            size_t curRepeat = 0;

            while(curRepeat++ < completeRepeats)
            {
                memcpy(ctx->dstBufPos, ctx->dstBufPos - offset, offset);
                ctx->dstBufPos += offset;
            }

            size_t rest = len % offset;
            memcpy(ctx->dstBufPos, ctx->dstBufPos - rest, rest);
            
            ctx->dstBufPos += rest;
            
            needLen = false;
        }
    }
    //normal adding 
    else 
    {
        memcpy(ctx->dstBufPos, ctx->dstBufPos - offset, len);  
    }

    if ( needLen )  ctx->dstBufPos += len;
    *ctx->dstBufPos = nextChr;
    ctx->dstBufPos++;

    #if defined(debug) && debug > 1
    __lz77_print_cur_dst_buf(ctx);
    #endif
}

void __lz77_decode(lz77CtxPtr _ctx)
{
    lz77CtxPtr ctx = _ctx;

    lz77BufPtr srcBuf = ctx->srcBuf;

    __lz77_calc_size_and_init_dst_buf(ctx);

    uint8_t *curLenBytePtr = srcBuf->bytes, *srcBufEndPtr = srcBuf->bytes + srcBuf->numBytes, nextChr = 0, curByte = 0;
    uint32_t len = 0, offset = 0;

    while ( curLenBytePtr < srcBufEndPtr )
    {
        curByte = *curLenBytePtr;
        len = curByte >> 0x4;
        offset = ((curByte & 0xF) << 0x4) | *(curLenBytePtr + 1);
        nextChr = *(curLenBytePtr + 2);
        
        #if defined(debug) && debug > 1
            printf("l: %i, o: %i n: %c \n", len, offset, nextChr);
        #endif

        __lz77_extend_dst_buf(ctx, &len, &offset, &nextChr);

        curLenBytePtr += TRIPLET_SIZE;
    }

}

/***** PUBLIC INTERFACE *****/

lz77_result_t en_lz77_u8(lz77BufPtr srcBuf, lz77BufPtr dstBuf, lz77ParamPtr param)
{
    lz77_ctx_t ctx;

    __lz77_init_ctx(&ctx, srcBuf, dstBuf, param);

    __lz77_encode(&ctx);

    return LZ77_OK;
}

lz77_result_t de_lz77_u8(lz77BufPtr srcBuf, lz77BufPtr dstBuf)
{
    lz77_ctx_t ctx;

    __lz77_init_ctx(&ctx, srcBuf, dstBuf, NULL);

    lz77_result_t result = LZ77_OK; 

    if ( __lz77_cnt_triplets_valid(ctx.srcBuf) )
    {
        __lz77_decode(&ctx);
    }
    else 
    {
        result = LZ77_ERR;
    }

    return result;
}

size_t lz77_get_dst_buf_size(lz77BufPtr srcBuf)
{
    return __lz77_calc_dst_buf_size(srcBuf);
}

