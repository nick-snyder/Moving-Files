#include <stdio.h>

unsigned long frameCount(void);

// if the address of the current frame is lower than the previous frame, 
// the last frame on the stack was the last frame

int main()
{
    printf("frame in main(): %ld\n", frameCount());
    return 0;
}