#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

int32_t f2i(uint32_t);

int main()
{    
    // compare f2i output to floats casted to ints
    for (int i = 0x5678800; i < 0x567890ac; i++)
    {
        // show every conversion
        printf("%x, %x\n", f2i(i), (int32_t) *(int32_t*)&i);
        
        if(f2i(i) != (int32_t) *(float *)&i) 
        {
            printf("%x != %x\n", f2i(i), (int32_t) *(float *)&i);
            assert(false);
        }
    }

    return 0;
}