#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{	
	FILE *fileIn = fopen(argv[1], "r");
	FILE *fileOut = fopen(argv[2], "w");

	unsigned char in;
	for (int i = 0; i < 4; i++)
	{
		// eat up utf8 BOM
		in = getc(fileIn);
	}
	
	// utf16 BOM
	putc(0xfe, fileOut);
	putc(0xff, fileOut);

	// while the token is not the end of the file (EOF)....	(xxxxxxxx)
	while (in != (unsigned char) EOF)
	{
		// check size
		if (in > 0x7F)		// 0 111 1111
		{
			unsigned char b = getc(fileIn);
			printf("2-byte sequence: %x %x\n", in, b);

			// cut off non data bits
			// only need to support two byte sequences
			// 11 bits: 110xxxxx 10xxxxxx
			unsigned char s1 = in << 3;				// 110xxxxx -> xxxxx000
			unsigned char s2 = b << 2;				// 10xxxxxx -> xxxxxx00
			unsigned int s3 = (unsigned int) s1;	// xxxxx000 -> 00000000 xxxxx000
			unsigned int s4 = s3 << 5;				// 00000000 xxxxx000 -> 000xxxxx 00000000
			unsigned int s5 = s4 | s2;				// 000xxxxx xxxxxx00
			unsigned int s6 = s5 >> 2;				// 000xxxxx xxxxxx00 -> 00000xxx xxxxxxxx

			// prepare to be added to output
			// putc can only add char (8bits) at a time
			// put msB first, then lsB
			unsigned char o1 = s6 & 0xFF;			// xxxxxxxx
			unsigned char o2 = s6 >> 8;				// 00000xxx

			// put into output file
			// Big Endian?
			putc(o1, fileOut);
			putc(o2, fileOut);
			printf("output: %x%x\n", o2, o1);
		}
		else
		{
			printf("1-byte sequence: %x\n", in);
			
			// put into output file
			// Big Endian?
			putc(0x00, fileOut);
			putc(in, fileOut);
		}

		// get next byte
		in = getc(fileIn);
	}

	fclose(fileIn);
	fclose(fileOut);

	return 0;
}
