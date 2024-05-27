#include "deflate.h"

#include "checksum.h"
#include "lz77.h"

#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "debug.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

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

#if defined(debug)
static void test_lz77_print_buffer_hex(const lz77BufPtr _bufEncodedPtr)
{
	const lz77BufPtr bufEncodedPtr = _bufEncodedPtr;
	size_t len = bufEncodedPtr->numBytes;
	DEBUG_LOG_ARGS("decoded len: %lli\n", len);
	for (size_t curChar = 0; curChar < len; curChar++)
	{
		printf("/0x%x", bufEncodedPtr->bytes[curChar]);
	}
	printf("\n");
}

static void test_lz77_print_buffer(const lz77BufPtr _bufPtr)
{
	const lz77BufPtr bufPtr = _bufPtr;
	size_t len = bufPtr->numBytes;
	DEBUG_LOG_ARGS("buffer len: %lli => \"", len);
	for (size_t curChar = 0; curChar < len; curChar++)
	{
		printf("%c", bufPtr->bytes[curChar]);
	}
	printf("\"\n");
}
#endif 

static void __write_lz77Buffer_to_File(const char *filename, const char *_txt, lz77BufPtr bufPtr)
{
	FILE *fptr;

	fptr = fopen(filename, "w");

	if ( fptr == NULL )
	{
		DEBUG_LOG_ARGS("Could not open File: %s\n", filename);
		return;
	}

	fprintf(fptr, (const char *)_txt);
	fprintf(fptr, "\n");
	fprintf(fptr, (const char *)bufPtr->bytes);

	// Close the file
	fclose(fptr); 
}

static void test_compression_lz77_single_test(const char *_txt, const char *_cap, uint16_t searchBufferSize, 
											  uint16_t lookAheadBufferSize, bool writeDecodeToFile)
{
	DEBUG_LOG_ARGS("\n################ %s #################### \n\n", _cap);

	LZ77Buf bufText;
	lz77BufPtr bufTextPtr = &bufText;

	unsigned char *txt = (unsigned char *)_txt;
	bufTextPtr->bytes = (uint8_t*)txt;
	bufTextPtr->numBytes = strlen(_txt); //-1 no termination byte processing

	DEBUG_LOG_ARGS("ENCODE TEST BYTE CNT: %lli\n", bufTextPtr->numBytes);

	LZ77Buf bufEncoded;
	lz77BufPtr bufEncodedPtr = &bufEncoded;
	LZ77Result result = LZ77_ERR;

	LZ77Param paramEncoding;
	paramEncoding.searchBufSize = searchBufferSize;
    paramEncoding.lookaheadBufSize = lookAheadBufferSize;
	lz77ParamPtr paramEncodingPtr = &paramEncoding;

	result = en_lz77_u8(bufTextPtr, bufEncodedPtr, paramEncodingPtr);
	
	assert(result == LZ77_OK);

	#if defined(debug)
	test_lz77_print_buffer_hex((const lz77BufPtr)bufEncodedPtr);
	#endif 

	assert(bufEncodedPtr->numBytes > 0);

	LZ77Buf bufDecoded;
	lz77BufPtr bufDecodedPtr = &bufDecoded;

	result = LZ77_ERR;
	result = de_lz77_u8(bufEncodedPtr, bufDecodedPtr);

	DEBUG_LOG_ARGS("Original:\"%s\"\n", _txt);
	#if defined(debug)
	test_lz77_print_buffer(bufDecodedPtr);
	#endif
	assert(result == LZ77_OK);

	if (writeDecodeToFile)
	{
		__write_lz77Buffer_to_File("dump_file2.txt", _txt, bufDecodedPtr);
	}

	int rsCmp = memcmp(_txt, bufDecodedPtr->bytes, bufDecodedPtr->numBytes);

	if (rsCmp != 0)
	{
		for ( uint32_t curByteIdx = 0; curByteIdx < bufDecodedPtr->numBytes; curByteIdx++)
		{
			if ( _txt[curByteIdx] != bufDecodedPtr->bytes[curByteIdx] )
			{
				DEBUG_LOG_ARGS("First difference at pos: %i of %i\n", curByteIdx, bufDecodedPtr->numBytes);
				break;
			}
		}
	}

	assert(rsCmp == 0);

	free(bufEncodedPtr->bytes);
	free(bufDecodedPtr->bytes);
}

static void test_compression_lz77_file(const char *filename, const char *_cap, uint16_t searchBufferSize, 
											  uint16_t lookAheadBufferSize, bool writeDecodeToFile)
{
	DEBUG_LOG_ARGS("\n################ %s (%s) #################### \n\n", _cap, filename);
	FILE *fptr;

	// Open a file in read mode
	fptr = fopen(filename, "r");

	if (fptr == NULL) {
		DEBUG_LOG_ARGS("Test File Error: %s ... abort\n", filename);
		return;
	}
	
	//File size
	fseek(fptr, 0L, SEEK_END);
	int fileSize = ftell(fptr);
	
	DEBUG_LOG_ARGS("File Size: %i\n", fileSize);
	
	// Store the content of the file
	char *buffer = malloc((sizeof(char) * fileSize) + 1);
	char *curBuff = buffer;
	//return to start 
	rewind(fptr);

	// Read the content
	while (!feof(fptr)) {
        *curBuff = (char)fgetc(fptr);
		#if defined(debug)
        printf("%c", *curBuff);
		#endif
		curBuff++;
    }
	*curBuff = '\0';

	test_compression_lz77_single_test((const char *)buffer, _cap, searchBufferSize, lookAheadBufferSize, writeDecodeToFile);

	free(buffer);
	// Close the file
	fclose(fptr); 
}

static void test_compression_lz77()
{
	DEBUG_LOG(">> Start lz77 tests:\n");

	test_compression_lz77_single_test("ababcbababaa", "Wiki Example", 15, 15, false);
	test_compression_lz77_single_test("ababccccccccccRSRSRSRSRSRSbababsowatsowasowatsowa", "Test 1", 30, 30, false);
	test_compression_lz77_single_test("aaaaaaaaaaaaaaaaaaaaRSTbbbbbbbbbbbbbbbGFcccccccccccc", "Repeat Test 1", 30, 30, false);
	test_compression_lz77_single_test("aaaaaaaaaaaaaaa", "15 Same Chars", 30, 30, false);
	test_compression_lz77_single_test("aaaaaaaaaaaaaaaa", "16 Same Chars", 30, 30, false);
	test_compression_lz77_single_test("aaaaaaaaaaaaaaaaa", "17 Same Chars", 30, 30, false);
	test_compression_lz77_single_test("aaaaaaaaaaaaaaaaaa", "18 Same Chars", 30, 30, false);
	test_compression_lz77_single_test("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "60 Same Chars", 30, 30, false);
	test_compression_lz77_single_test("ababRSTRSTRSTRSTRSTRSTRSTRSTblubb", "Repeat-1: Triplet overflow", 30, 30, false);
	test_compression_lz77_single_test("RSTRSTRSTRSTRSTRSTRSTRST", "Repeat-2: Triplet overflow", 30, 30, false);
	test_compression_lz77_single_test("RSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRSTRST", "Repeat-3: Higher Triplet overflow", 60, 60, false);
	test_compression_lz77_single_test("0123456789ABCDEFGHIJK0123456789ABCDEFGHIJK0123456789ABCDEFGHIJK0123456789ABCDEFGHIJK", "Found: Bytes repeat Triplet overflow", 256, 256, false);
	test_compression_lz77_single_test("eine Quadraturamplitudenmodulation eine eine Quadraturamplitudenmodulation bezeichnet!!", "Found: Triplet overflow", 256, 256, false);
	test_compression_lz77_single_test("At accusam aliquyam diam diam dolore dolores duo eirmod", "Regression 1: Error from File", 5000, 5000, false);
	test_compression_lz77_single_test("Lorem ipsum dolor sit amet, Lorem ipsum dolor sit amet, consetetur sadipscing elitr,  sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.", "Regression 2: Error from File", 5000, 5000, false);
	
	test_compression_lz77_file("test_file_1.txt", "Test File 1", 30, 5000, false);
	test_compression_lz77_file("test_file_2.txt", "Test File 2", 5000, 5000, false);
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