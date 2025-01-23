#include <stdio.h>

int frameCount(void);
int addFrame(int);
void testFrame1(void);
void testFrame2(void);
void testFrame3(void);

// if the address of the current frame is lower than the previous frame, 
// the last frame on the stack was the last frame

int main()
{
    printf("frame in main(): %d\n", addFrame(0));
    testFrame1();
    return 0;
}

int addFrame(int n)
{
    if (n < 20)
    {
        
        n = addFrame(++n);
    }
    else
    {
        printf("frame in addFrame(): %d\n", frameCount());
    }
    return n;
}

void testFrame1()
{
    testFrame2();
}
void testFrame2()
{
    testFrame3();
}
void testFrame3()
{
    printf("frame in testFrame3(): %d\n", frameCount());
}