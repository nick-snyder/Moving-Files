void *getFP(void);

    // fix frameCount
    // finish printFrames

// display the contents on the stack, frame by frame 
// starting with the topmost (most recent) frame and 
// working your way backwards until there are no more 
// frames on the stack
void printFrames()
{
    printf("List of Frames:\n");
    long f1 = frameCount();
    long f2 = frameCount();
    printf("%lx\n", f1);
    printf("%lx\n", f2);

    printf("\nStack Pointer: %lx\n", sp);
    printf("Frame Pointer: %lx\n", f1);

    printf("Current frame:\n");
    long cf = sp;
    while (cf != f2)
    {
        printf("[%lx] %lx\n", cf, *cf);
        cf = frameCount();
    }

    for (int i = 0; i < numFrames; i++)
    {
        printf("\nPrevious frame:\n");
        printf("[%lx] %lx saved %%rip\n", , );
        while ()
        {
            printf("[%lx] %lx\n", , );
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
    void *fp = getFP();

    while (fp) 
    {
        fp = *(void**) fp;
        i++;
    }

    return i;
}

int main()
{
    // test driver
}