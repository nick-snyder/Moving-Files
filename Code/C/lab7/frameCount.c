#include <stdio.h>

long getFP(void);

// starting from the current frame
// void *currentFrame = getFP();

int frameCount()
{
    // This count should not include the function performing the count.
    // The count should include the main() function’s frame but not the caller of main.
    // Starting from the current frame (which is what getFP() will return), 
    // you should be able to follow the list of frames currently on the stack.
    // Look for some way to identify the last frame on the stack

    int i = 0;

    long currentFrame = getFP();
    // long nextFrame = currentFrame;

    // follow the list of frames on the stack
    // count the number of stack frames starting from the frame pointer to the stack pointer

    while (currentFrame <= *(long *) currentFrame)
    {
        // printf("current frame: %lx\n", currentFrame);

        currentFrame = *(long *) currentFrame;

        i++;
    }

    return i;
}
