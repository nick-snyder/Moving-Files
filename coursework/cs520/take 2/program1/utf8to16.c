#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#define DEBUG

bool readBOM(FILE *fileIn)
{
	// big if true, little if false
	bool endianness;

	// eat up old UTF-16 BOM "feff78" -> "78"
	unsigned int token = getc(fileIn);
	
	// determine endianness
	if (token == 0xef)
	{
		endianness = true;
	}
	else
	{
		endianness = false;
	}

	// eat up rest of BOM
	token = getc(fileIn);
	token = getc(fileIn);

	return endianness;
}

void writeBOM(FILE* fileOut)
{
	putc(0xfe, fileOut);
	putc(0xff, fileOut);
}

int decode(bool endianness, unsigned int token1, FILE* fileIn)
{
	// read in second token
	if (token1 < 0x80)
	{
		return token1;
	}

	else if (token1 < 0xe0)
	{
		unsigned int token2 = getc(fileIn);

		return ((token1 & 0x3f) << 6) | (token2 & 0x7f);
	}

	else if (token1 < 0xf0)
	{
		unsigned int token2 = getc(fileIn);
		unsigned int token3 = getc(fileIn);

		return ((token1 & 0x0f) << 12) | ((token2 & 0x7f) << 6) | (token3 & 0x7f);
	}

	else if (token1 < 0xf8)
	{
		unsigned int token2 = getc(fileIn);
		unsigned int token3 = getc(fileIn);
		unsigned int token4 = getc(fileIn);

		return ((token1 & 0x0f) << 18) | ((token2 & 0x7f) << 12) | ((token3 & 0x7f) << 6) | (token4 & 0x7f);
	}

	return 0;
}

void encode(unsigned int unicode, FILE* fileOut)
{
	// 0xxxxxxx
	if (unicode < 0x80)
	{
		putc(0x00, fileOut);
		putc(unicode, fileOut);
	}

	// 00000xxx xxxxxxxx
	else if (unicode < 0x8000)
	{
		putc(unicode >> 8, fileOut);
		putc(unicode, fileOut);
	}

	// xxxxxxxx xxxxxxxx
	else if (unicode < 0x10000)
	{
		putc(unicode >> 8, fileOut);
		putc(unicode, fileOut);
	}

	// 000xxxxx xxxxxxxx xxxxxxxx
	else if (unicode < 0x200000)
	{
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
	}
}

int main(int argc, char *argv[])
{	
	// open input and output files
	FILE *fileIn = fopen(argv[1], "r");
	FILE *fileOut = fopen(argv[2], "w");

	// FILE *fileIn = fopen("utf8-val-ABCDE", "r");
	// FILE *fileOut = fopen("OUTPUT_UTF8TO16-VAL-ABCDE", "w");

	bool endianness = readBOM(fileIn);

	writeBOM(fileOut);

	unsigned int token = getc(fileIn);

	while (token != EOF)
	{
		unsigned int unicode = decode(endianness, token, fileIn);

		encode(unicode, fileOut);

		token = getc(fileIn);
	}

	// close files
	fclose(fileIn);
	fclose(fileOut);

	return 0;
}
