#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// #define DEBUG

bool readBOM(FILE *fileIn)
{
	// big if true, little if false
	bool endianness;

	// eat up old UTF-16 BOM "feff78" -> "78"
	unsigned int token = getc(fileIn);
	
	// determine endianness
	if (token == 0xfe)
	{
		endianness = true;
	}
	else
	{
		endianness = false;
	}

	// eat up rest of BOM
	token = getc(fileIn);

	return endianness;
}

void writeBOM(FILE* fileOut)
{
	putc(0xef, fileOut);
	putc(0xbb, fileOut);
	putc(0xbf, fileOut);
}

int decode(bool endianness, unsigned int token1, FILE* fileIn)
{
	// read in second token
	// unsigned int token2 = getc(fileIn);

	if ((token1 < 0xd800) && (token1 > 0xdbff))
	{
		// lead surrogate detected
		unsigned int token2 = getc(fileIn);
		unsigned int token3 = getc(fileIn);
		unsigned int token4 = getc(fileIn);

		unsigned int leadSurrogate = ((token1 << 24) | (token2 << 16)) - 0xd800;
		unsigned int trailSurrogate = ((token3 << 8) | token4) - 0xdc00;

		// xxxxxxxx xxxxxxxx
		leadSurrogate = leadSurrogate << 10;

		//
		trailSurrogate = ~(trailSurrogate & 0x3ff);

		unsigned int nonBMP = (leadSurrogate << 16) | trailSurrogate;

		return nonBMP + 0x10000;

		/*
		// non-BMP
		unsigned int nonBMP = unicode - 0x10000;

		//
		unsigned int leadSurrogate = (nonBMP >> 10) + 0xd800;

		//
		unsigned int trailSurrogate = (nonBMP & 0x3ff) + 0xdc00;

		nonBMP = (leadSurrogate << 16) | trailSurrogate;

		putc(nonBMP << 24, fileOut);
		putc(nonBMP << 16, fileOut);
		putc(nonBMP << 8, fileOut);
		putc(nonBMP, fileOut);
		*/

		// return (token1 << 24) | (token2 << 16) | (token3 << 8) | token4;
	}

	// read in second token
	unsigned int token2 = getc(fileIn);

	if (endianness)
	{
		// big endian
		return (token1 << 8) | token2;
	}
	else
	{
		// little endian
		return (token2 << 8) | token1;
	}
}

void encode(unsigned short unicode, FILE* fileOut)
{
	if (unicode < 0x0080)
	{
		// one-byte sequence
		putc(unicode, fileOut);		// 0xxxxxxx
	}
	
	else if (unicode < 0x0800)
	{
		// two-byte sequence
		unsigned char leadByte = 0xc0 | (unicode >> 6);				// 110xxxxx
		unsigned char continuationByte = (0xbf & unicode) | 0x80;	// 10xxxxxx

		putc(leadByte, fileOut);
		putc(continuationByte, fileOut);
	}

	else if (unicode < 0x10000)
	{
		// three-byte sequence
		unsigned char leadByte = 0xe0 | (unicode >> 12);					// 1110xxxx
		unsigned char continuationByte1 = (0xbf & (unicode >> 6)) | 0x80;	// 10xxxxxx
		unsigned char continuationByte2 = (0xbf & unicode) | 0x80;			// 10xxxxxx

		putc(leadByte, fileOut);
		putc(continuationByte1, fileOut);
		putc(continuationByte2, fileOut);
	}

	else if (unicode < 0x200000)
	{
		// four-byte sequence
		unsigned char leadByte = 0xf7 | (unicode >> 18);
		unsigned char continuationByte1 = (0xbf & (unicode >> 12)) | 0x80;
		unsigned char continuationByte2 = (0xbf & (unicode >> 6)) | 0x80;
		unsigned char continuationByte3 = (0xbf & unicode) | 0x80;

		putc(leadByte, fileOut);
		putc(continuationByte1, fileOut);
		putc(continuationByte2, fileOut);
		putc(continuationByte3, fileOut);
	}
}

// open files
// read BOM and determine endianness
// decode utf-16 to unicode
// encode unicode to utf-8

int main(int argc, char *argv[])
{
	FILE *fileIn = fopen(argv[1], "r");
	FILE *fileOut = fopen(argv[2], "w");

	// FILE *fileIn = fopen("utf16-3-be", "r");
	// FILE *fileOut = fopen("OUTPUT_UTF8-7", "w");

	bool endianness = readBOM(fileIn);

	writeBOM(fileOut);

	unsigned int token = getc(fileIn);

	while (token != EOF)
	{
		unsigned int unicode = decode(endianness, token, fileIn);

		encode(unicode, fileOut);

		token = getc(fileIn);
	}

	fclose(fileIn);
	fclose(fileOut);

	return 0;
}
