#include "crypt.h"

#include <stdint.h>
#include <assert.h>

#include "debug.h"

const unsigned char * test_str(uint32_t len)
{
	static const unsigned char* test = (const unsigned char*)"123456789012345678901234567890123456789012345678901234567890";
	return test + (strlen((const char*)test) - len);
}

static void test_b64_len_fn()
{
	DEBUG_LOG(">> Start b64 len tests:\n");

	const unsigned char *test = NULL; 
	const size_t cntValues = 24;
	const uint32_t sizeValues[] = { 4,4,4,8,8,8,12,12,12,16,16,16,20,20,20,24,24,24,28,28,28,32,32,32};

	for ( uint32_t valueIdx = 0; valueIdx < cntValues; valueIdx++ )
	{
		test = test_str(valueIdx + 1);
		DEBUG_LOG_ARGS("teststr: %s\n", test);
		assert(b64maxLenEncStr(test) == sizeValues[valueIdx]);
	}

	assert(b64maxLenDecStr(test_str(4)) == 3);
	assert(b64maxLenDecStr(test_str(8)) == 6);
	assert(b64maxLenDecStr(test_str(12)) == 9);
	assert(b64maxLenDecStr(test_str(16)) == 12);
	assert(b64maxLenDecStr(test_str(20)) == 15);
	assert(b64maxLenDecStr(test_str(24)) == 18);
	assert(b64maxLenDecStr(test_str(28)) == 21);
	assert(b64maxLenDecStr(test_str(32)) == 24);

	DEBUG_LOG("<< end b64 len tests:\n");	
}

int main(int argc, char **argv) {
	(void)argc; (void)argv;

	DEBUG_LOG(">> Start crypt tests:\n");

	test_b64_len_fn();

	DEBUG_LOG("<< end crypt tests:\n");

	return 0;
}