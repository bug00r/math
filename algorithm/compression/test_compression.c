#include "deflate.h"

#include "checksum.h"
#include "lz77.h"

#include <stdint.h>
#include <assert.h>

#include "debug.h"

static void test_compression_crc32()
{
	DEBUG_LOG(">> Start crc32 tests:\n");

	unsigned char test[12] = {'H','a','l','l','o',' ','W','e','l','t','!','!'};

	uint32_t checksum = crc32_u8(&test[0], 12);

	assert(checksum == 0xC9BD1EA4);

	uint32_t checksum2 = crc32_uc(&test[0], 12);

	assert(checksum2 == 0xC9BD1EA4);

	DEBUG_LOG("<< end crc32 tests:\n");
}

static void test_compression_lz77()
{
	DEBUG_LOG(">> Start lz77 tests:\n");

	lz77_buf_t bufText;
	lz77BufPtr bufTextPtr = &bufText;

	unsigned char txt[] = "ababcbababaa";
	bufTextPtr->bytes = (uint8_t*)&txt[0];
	bufTextPtr->numBytes = sizeof(txt);

	//lz77_buf_t bufEncoded;
	//lz77BufPtr bufEncodedPtr = &bufEncoded;
	lz77BufPtr bufEncodedPtr;
	lz77_result_t result = LZ77_ERR;

	lz77_param_t paramEncoding;
	paramEncoding.searchBufSize = 16;
    paramEncoding.lookaheadBufSize = 16;
	lz77ParamPtr paramEncodingPtr = &paramEncoding;

	result = en_lz77_u8(bufTextPtr, &bufEncodedPtr, paramEncodingPtr);
	
	assert(result == LZ77_OK);

	//lz77_buf_t bufDecoded;
	//lz77BufPtr bufDecodedPtr = &bufDecoded;
	lz77BufPtr bufDecodedPtr;

	result = LZ77_ERR;
	result = de_lz77_u8(bufEncodedPtr, &bufDecodedPtr);

	assert(result == LZ77_OK);

	DEBUG_LOG("<< end lz77 tests:\n");
}

static void test_compression_deflate()
{
	DEBUG_LOG(">> Start deflate tests:\n");

	DEBUG_LOG("<< end deflate tests:\n");
}

int main(int argc, char **argv) {
	(void)argc; (void)argv;

	DEBUG_LOG(">> Start compression tests:\n");

	test_compression_crc32();

	test_compression_lz77();

	test_compression_deflate();

	DEBUG_LOG("<< end compression tests:\n");

	return 0;
}