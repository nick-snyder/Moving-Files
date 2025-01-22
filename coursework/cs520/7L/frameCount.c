long getFP(void);

long frameCount()
{
    int i = 0;
    long fp = getFP();
    // long *sp = &fp;

    for (long fp = getFP(); fp; fp = *(long*) fp) 
    {
        i++;
    }

    return i;
}
