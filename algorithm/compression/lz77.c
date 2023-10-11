#include "lz77.h"

/***** PRIVATE INTERFACE *****/
typedef struct __lz77_buf_pos
{
    uint8_t *start;
    uint8_t *end;
} lz77_buf_pos_t;

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

static void __lz77_init_algo(lz77CtxPtr _ctx, lz77BufPtr srcBuf, lz77BufPtr* dstBuf, lz77ParamPtr param)
{
    lz77CtxPtr ctx = _ctx;
    ctx->pos = &srcBuf->bytes[0]; 
    ctx->srcBuf = srcBuf;
    ctx->dstBuf = dstBuf;
    ctx->param = param;
}

/***** PUBLIC INTERFACE *****/

lz77_result_t en_lz77_u8(lz77BufPtr srcBuf, lz77BufPtr* dstBuf, lz77ParamPtr param)
{
    lz77_ctx_t ctx;
    __lz77_init_algo(&ctx, srcBuf, dstBuf, param);

    return LZ77_OK;
}

lz77_result_t de_lz77_u8(lz77BufPtr srcBuf, lz77BufPtr* dstBuf)
{
    return LZ77_OK;
}

