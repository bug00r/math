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

typedef struct __b64_enc_test_data
{
	const unsigned char *text;
	const char *b64Text;
	bool padding;
} b64encdata_t;

static const b64encdata_t b64enctestdata[] = { 
	{(const unsigned char *)"Ma", "TWE=", true} ,
	{(const unsigned char *)"M", "TQ==", true} ,
	{(const unsigned char *)"light work", "bGlnaHQgd29yaw==", true} ,
	{(const unsigned char *)"Dies ist ein langer Text!!", "RGllcyBpc3QgZWluIGxhbmdlciBUZXh0ISE=", true} ,
	{(const unsigned char *)"Ma", "TWE", false} ,
	{(const unsigned char *)"M", "TQ", false} ,
	{(const unsigned char *)"light work", "bGlnaHQgd29yaw", false} ,
	{(const unsigned char *)"Dies ist ein langer Text!!", "RGllcyBpc3QgZWluIGxhbmdlciBUZXh0ISE", false},
	{ NULL, NULL, false},
};

static void __test_b64_enc_(const unsigned char *text, const char *expectedResult, bool padding)
{
	uint8_t *result = b64encode((uint8_t*)text, strlen((const char*)text), padding);
	DEBUG_LOG_ARGS("test: %s => encode: %s\n", (char*)text, (char*)result);
	assert(strcmp((const char*)result, (const char*)expectedResult) == 0);
	free(result);
}

static void test_b64_encrypt()
{
	DEBUG_LOG(">> Start b64 encrypt tests:\n");

	for ( size_t testDataIdx = 0; b64enctestdata[testDataIdx].text != NULL; testDataIdx++)
	{
		const b64encdata_t* testData = &b64enctestdata[testDataIdx];
		__test_b64_enc_(testData->text, testData->b64Text, testData->padding);
	}

	DEBUG_LOG("<< end b64 encrypt tests:\n");	
}

static void __test_b64_dec_(const char *text, const unsigned char *expectedResult, bool padding)
{
	uint8_t *result = b64decode((uint8_t*)text, strlen(text), padding);
	DEBUG_LOG_ARGS("test: %s => decode: %s\n", (char*)text, (char*)result);
	assert(strcmp((const char*)result, (const char*)expectedResult) == 0);
	free(result);
}

static void test_b64_decrypt()
{
	DEBUG_LOG(">> Start b64 encrypt tests:\n");

	for ( size_t testDataIdx = 0; b64enctestdata[testDataIdx].text != NULL; testDataIdx++)
	{
		const b64encdata_t* testData = &b64enctestdata[testDataIdx];
		__test_b64_dec_(testData->b64Text, testData->text, testData->padding);
	}

	DEBUG_LOG("<< end b64 encrypt tests:\n");	
}

int main(int argc, char **argv) {
	(void)argc; (void)argv;

	DEBUG_LOG(">> Start crypt tests:\n");

	test_b64_len_fn();

	test_b64_encrypt();

	test_b64_decrypt();

	DEBUG_LOG("<< end crypt tests:\n");

	return 0;
}