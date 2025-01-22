#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// big endian

int main(int argc, char *argv[])
{

	// while file is not empty
	// read/getc next bit in sequence
	
	FILE *fileIn = fopen(argv[1], "r");
	FILE *fileOut = fopen(argv[2], "w");

	unsigned char a;
	int i = 0;

	// BOM
	putc(0xfe, fileOut);
	putc(0xff, fileOut);

	// for each byte in the file....
	while (a != (unsigned char) EOF)
	{
		if (i > 3)
		{
			// bitwise AND
			unsigned char b = 0xC0;
			unsigned char c = a & b;

			// Character
			putc(0x00, fileOut);
			putc(a, fileOut);
		}

		a = getc(fileIn);
		//printf("%x ", a);
		i++;
	}

	//printf("\n");

	fclose(fileIn);
	fclose(fileOut);

	return 0;
}
