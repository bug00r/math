#include "deflate.h"

#include "checksum.h"

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