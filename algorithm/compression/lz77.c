#include "lz77.h"

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
    /* sliding window, depends on current processing position */ 
    lz77_sliding_window_t slWin;
    /* Buffer with bytes to compress */
    lz77BufPtr  srcBuf; 
    /* Buffer with result bytes */
    lz77BufPtr  *dstBuf;
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

static bool __lz77_lookahed_buffer_available(lz77CtxPtr _ctx)
{
    lz77CtxPtr ctx = _ctx;
    lz77BufPosPtr lookAheadBufPos = &ctx->slWin.laBuf;

    return ( lookAheadBufPos->start != lookAheadBufPos->end );
}

static void __lz77_set_lookahed_buffer(lz77CtxPtr _ctx)
{
    lz77CtxPtr ctx = _ctx;
    lz77BufPosPtr lookAheadBufPos = &ctx->slWin.laBuf;
    lz77BufPtr srcBuffer = ctx->srcBuf;

    uint8_t *endSrcBuf = &srcBuffer->bytes[0] + srcBuffer->numBytes - 1;
    
    uint16_t paramLaBufSize = ctx->param->lookaheadBufSize;
    size_t maxPossLaBufSize = endSrcBuf - ctx->pos;

    if ( maxPossLaBufSize )
    {
        uint16_t curLaBufSize = ( maxPossLaBufSize < paramLaBufSize ? maxPossLaBufSize : paramLaBufSize );

        lookAheadBufPos->start = ctx->pos;
        lookAheadBufPos->start = ctx->pos + curLaBufSize;
    }
    else 
    {
        lookAheadBufPos->start = ctx->pos;
        lookAheadBufPos->end = ctx->pos;
    }

}

static void __lz77_set_sliding_window(lz77CtxPtr _ctx)
{
    lz77CtxPtr ctx = _ctx;

    __lz77_set_search_buffer(ctx);
    __lz77_set_lookahed_buffer(ctx);
}

static void __lz77_init_algo(lz77CtxPtr _ctx, lz77BufPtr srcBuf, lz77BufPtr* dstBuf, lz77ParamPtr param)
{
    lz77CtxPtr ctx = _ctx;
    ctx->pos = &srcBuf->bytes[0]; 
    ctx->srcBuf = srcBuf;
    ctx->dstBuf = dstBuf;
    
    //Destination Buffer will be cleared at Beginning
    *ctx->dstBuf = NULL;

    ctx->param = param;
}

/* currently not using bitfields because lib should be usable with c99 too*/
typedef struct __lz77_triplet 
{
    uint8_t bytes[3];
} lz77_priplet_t,*lz77TripletPtr;

static void __lz77_pack_triplet(lz77TripletPtr _curTriplet, 
                                uint32_t *_offset, uint32_t *_len, uint8_t *_chr)
{
    lz77TripletPtr curTriplet = _curTriplet;
    uint32_t offset = *_offset, len = *_len;
    uint8_t chr = *_chr;

    //TODO packing into Byte Array from Triplet Pointer

    #if defined(debug) && debug != 0
    printf("packed(o,l,c) => bytes: (%i,%i,%c) => (%c,%c,%c)\n",
            offset, len, chr, 
            curTriplet->bytes[0],curTriplet->bytes[1],curTriplet->bytes[2]);
    #endif
} 

static void __lz77_search_triplet(lz77CtxPtr _ctx, 
                                  uint32_t *_offset, uint32_t *_len, uint8_t *_chr)
{
    lz77CtxPtr ctx = _ctx;
    uint32_t offset = *_offset, len = *_len;
    uint8_t chr = *_chr;

    //TODO implement seach details

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

    __lz77_pack_triplet(curTriplet, &offset, &len, &chr);

    ctx->pos += len;
    ctx->pos++;
}

static void __lz77_dump_triplet_to_dst_buffer(lz77CtxPtr _ctx, lz77TripletPtr _curTriplet)
{
    lz77CtxPtr ctx = _ctx;
    lz77TripletPtr curTriplet = _curTriplet;

    /*  TODO dumping triplet into dst buffer maybe allocating 
        chunks with 64,128, 256, 512 etc blocks(reducing sys calls for memory)
    */
}

static void __lz77_encode(lz77CtxPtr _ctx)
{
    lz77CtxPtr ctx = _ctx;
    lz77_priplet_t curTriplet;
    lz77TripletPtr curTripletPtr = &curTriplet;

    __lz77_set_lookahed_buffer(ctx);
    
    while ( __lz77_lookahed_buffer_available(ctx) ) 
    {    
        __lz77_set_search_buffer(ctx);

        /* mybe __lz77_search_buffer_available is not needed */
        __lz77_search_next_triplet(ctx, curTripletPtr);

        __lz77_dump_triplet_to_dst_buffer(ctx, curTripletPtr);

        __lz77_set_lookahed_buffer(ctx);
    } 
    

}

/***** PUBLIC INTERFACE *****/

lz77_result_t en_lz77_u8(lz77BufPtr srcBuf, lz77BufPtr* dstBuf, lz77ParamPtr param)
{
    lz77_ctx_t ctx;
    //TODO Check if buffer is available and correct
    __lz77_init_algo(&ctx, srcBuf, dstBuf, param);

    __lz77_encode(&ctx);

    return LZ77_OK;
}

lz77_result_t de_lz77_u8(lz77BufPtr srcBuf, lz77BufPtr* dstBuf)
{
    return LZ77_OK;
}

