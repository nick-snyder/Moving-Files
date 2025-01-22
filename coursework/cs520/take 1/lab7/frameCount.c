void *getFP(void);

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
