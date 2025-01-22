#include <stdio.h>

unsigned long frameCount();

void f(int a)
{
    for (char b = 'f'; b < 'h'; b++)
    {
        // printf("frame inside function f: %ld\n", frameCount());
    }
}

int g(int x)
{
    // printf("frame in recursive function g: %ld\n", frameCount());
    if (x > 1)
    {
        return g(x - 1);
    }
    return 0;
}

int main()
{
    int t = g(4);
    t++;

    // printf("frame in main(): %ld\n", frameCount());
    return 0;
}