#include <stdio.h>

int addFrame(int);
void testFrame1(void);
void testFrame2(void);
void testFrame3(void);

long frameCount(void);

long getFP(void);
long getSP(void);

// display the contents on the stack, frame by frame 
// starting with the topmost (most recent) frame and 
// working your way backwards until there are no more 
// frames on the stack
void printFrames()
{
    long currentFramePointer = getFP();

    printf("List of Frames:\n");
    printf("%lx\n", currentFramePointer);

    int numFrames = 1;
    for (long currentFrame = getFP(); currentFrame <= *(long *) currentFrame; currentFrame = *(long *) currentFrame)
    {
        printf("%lx\n", *(long *) currentFrame);
        numFrames++;
    }

    // array of "List of Frames"
    long frameArray[numFrames];
    // printf("num: %d\n", numFrames);

    // populate the frame array
    int j = 0;
    frameArray[0] = currentFramePointer;
    for (long currentFrame = getFP(); currentFrame <= *(long *) currentFrame; currentFrame = *(long *) currentFrame)
    {
        j++;
        frameArray[j] = *(long *) currentFrame;
    }

    // for (int k = 0; k < numFrames; k++)
    // {
    //     printf("print: %lx\n", frameArray[k]);
    // }

    // print the pointers
    printf("\nStack Pointer: %lx\n", getSP());
    printf("Frame Pointer: %lx\n", getFP());

    long currentStackPointer;

    // starting ar the stack pointer, print the contents of each current frame until you reach the next frame in the list
    for (int i = 0; i < numFrames; i++)
    {
        // print "Current frame:" only on first group of frames
        if (i == 0)
        {
            printf("\nCurrent frame:\n");

            // start at each frame and show contents until next frame
            for (currentStackPointer = getSP(); currentStackPointer <= frameArray[i]; currentStackPointer += 8)
            {
                printf("[%lx] %lx\n", currentStackPointer, *(long *) currentStackPointer);
            }
        }
        else
        {
            printf("\nPrevious frame:\n");
            for ( ; currentStackPointer <= frameArray[i]; currentStackPointer += 8)
            {
                printf("[%lx] %lx\n", currentStackPointer, *(long *) currentStackPointer);
            }
        }
    }

    // For every frame other than the current frame, you 
    // must also show where the (old) %rip register was 
    // saved, this is where the program will continue 
    // upon each function return
}

long frameCount()
{
    // This count should not include the function performing the count.
    // The count should include the main() function’s frame but not the caller of main.
    // Starting from the current frame (which is what getFP() will return), 
    // you should be able to follow the list of frames currently on the stack.
    // Look for some way to identify the last frame on the stack

    int i = 0;

    // starting from the current frame
    long currentFrame = getFP();

    // follow the list of frames on the stack
    // count the number of stack frames starting 
    // from the frame pointer to the stack pointer
    while (currentFrame <= *(long *) currentFrame)
    {
        currentFrame = *(long *) currentFrame;

        i++;

        // printf("f: %lx\n", currentFrame);
        // printf("[%lx] %lx\n", currentFrame, *(long *) currentFrame);
    }

    return i;
}

// int main()
// {
//     // printf("frame in main(): %d\n", addFrame(0));
//     // testFrame1();
//     printFrames();
//     return 0;
// }

int addFrame(int n)
{
    if (n < 20)
    {
        
        n = addFrame(++n);
    }
    else
    {
        printf("frame in addFrame(): %ld\n", frameCount());
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
    printf("frame in testFrame3(): %ld\n", frameCount());
}