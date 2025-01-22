#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{	
	FILE *fileIn = fopen(argv[1], "r");
	FILE *fileOut = fopen(argv[2], "w");

	unsigned char a;
	for (int i = 0; i < 4; i++)
	{
		// eat up utf16 BOM
		a = getc(fileIn);
	}

	// uft32 BOM
	// 00 00 FE FF
	putc(0xff, fileOut);
    putc(0xfe, fileOut);
	putc(0x00, fileOut);
	putc(0x00, fileOut);

	while (a != (unsigned char) EOF)
	{
		// check size?

		unsigned char b = getc(fileIn);
		unsigned char c = getc(fileIn);
		unsigned char d = getc(fileIn);

		// cut off non data bits
		// 21 bits: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		unsigned char s1 = a << 5;				// 11110xxx -> xxx00000
		unsigned char s2 = b << 2;				// 10xxxxxx -> xxxxxx00
		unsigned char s3 = c << 2;				// 10xxxxxx -> xxxxxx00
		unsigned char s4 = d << 2;				// 10xxxxxx -> xxxxxx00

		unsigned int s5 = (unsigned int) s1;	// xxx00000 -> 00000000 xxx00000
		unsigned int s6 = s5 >> 3;				// 00000000 xxx00000 -> 00000xxx 00000000
		unsigned int s7 = s6 | s2;				// 00000xxx xxxxxx00
		unsigned int s8 = s7 >> 2;				// 00000xxx xxxxxx00 -> 0000000x xxxxxxxx

		unsigned int s9 = (unsigned int) s3;	// xxxxxx00 -> 00000000 xxxxxx00
		unsigned int s10 = s9 << 6;				// 00000000 xxxxxx00 -> 00xxxxxx 00000000
		unsigned int s11 = s10 | s4;			// 00xxxxxx xxxxxx00
		unsigned int s12 = s11 << 2;			// 00xxxxxx xxxxxx00 -> xxxxxxxx xxxx0000

		unsigned long s13 = (unsigned long) s8;	// 0000000x xxxxxxxx -> 00000000 00000000 0000000x xxxxxxxx
		unsigned long s14 = s13 << 16;			// 00000000 00000000 0000000x xxxxxxxx -> 0000000x xxxxxxxx 00000000 00000000
		unsigned long s15 = s14 | s12;			// 0000000x xxxxxxxx xxxxxxxx xxxx0000
		unsigned long s16 = s15 >> 4;			// 0000000x xxxxxxxx xxxxxxxx xxxx0000 -> 00000000 000xxxxx xxxxxxxx xxxxxxxx

		// prepare to be added to output
		// putc can only add char (8bits) at a time
		// put msB first, then lsB
		unsigned char o1 = s16 & 0xFF;			// xxxxxxxx
		unsigned char o2 = s16 >> 8;			// xxxxxxxx
		unsigned char o3 = s16 >> 16;			// 000xxxxx
		unsigned char o4 = s16 >> 24;			// 00000000

		// put into output file
		// Big Endian?
		putc(o1, fileOut);
		putc(o2, fileOut);
		putc(o3, fileOut);
		putc(o4, fileOut);
		printf("output: %x%x%x%x\n", o4, o3, o2, o1);

		a = getc(fileIn);
	}

	fclose(fileIn);
	fclose(fileOut);

	return 0;
}