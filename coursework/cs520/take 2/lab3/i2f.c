//
// i2f: convert 32-bit two's complement integer to IEEE
// single-precision floating point.
//
// Remember when you implement the function you may not use the
// float or double types. Everything must be done using only integer
// types.

#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

static unsigned int findSign(int32_t in)
{
    return in >> 31;
}

static unsigned int findExponent(int32_t in)
{
    if (in >> 31)
    {
        in = (~in) + 1;
    }

    for (int i = 1; i < 32; i++)
    {
        // slide the int all the way to the left (>> 32) and each iteration slide back by one less (>> 32 - i)
        unsigned shiftedInt = in >> (32 - i);
        if (shiftedInt != (in >> 31))
        {
            return 32 - i + 127;
        }
    }

    return 0x00;

    // while leading 0, keep looping and increment
    // if 1, stop and keep count
}

static unsigned int findSignificand(int32_t in)
{
    // first 1 is ignored, second 1 starts the significand and goes to the end
    if (in >> 31)
    {
        in = (~in) + 1;
    }
    
    int i;
    for (i = 1; i < 32; i++)
    {
        // slide the int all the way to the left (>> 32) and each iteration slide back by one less (>> 32 - i)
        int shiftedInt = in >> (32 - i);
        if (shiftedInt != (in >> 31))
        {
            break;
        }
    }
    // i++;

    // hold significand
    unsigned significand = ((in << i) & 0xfffffe00) >> 9;
    // i = 3, 32-23-3=6
    // zzzXXXXXXXXXXXXXXXXXXXXXXXggssss
    // 000000zzzXXXXXXXXXXXXXXXXXXXXXXX
    // 00000000 0XXX XXXX XXXX XXXX XXXX XXXX

    // truncate or round

    // if there is more significand bits the needed
    if (i < (32 - 23))
    // i=3, 32-23=9
    // zzzXXXXXXXXXXXXXXXXXXXXXXXggssss
    // 
    {
        // expanded significand (in): 000sssssssssssssssssssssssggSSSS

        // regular significand (cuts off any bits after 23)
        // significand = in >> i;
        // 000000000sssssssssssssssssssssss

        // bits after the regular significand
        unsigned extraBits = ((unsigned int) in) << (23 + i) >> (23 + i);
        // i=3, 23+3=26
        // zzzXXXXXXXXXXXXXXXXXXXXXXXggssss
        // ggssss00000000000000000000000000
        // 00000000000000000000000000ggssss

        // next two bits after normal significand (always 2)
        unsigned guardBits = extraBits >> (32 - 23 - i - 2);
        // i=3, 32-23-3-2=4
        // 00000000000000000000000000ggssss
        // 000000000000000000000000000000gg

        // last bits after guard bits are sticky bits
        unsigned stickyBits = extraBits << (23 + 2 + i) >> (23 + 2 + i);
        // i=3, 23+2+3=28
        // 00000000000000000000000000ggssss
        // ssss0000000000000000000000000000
        // 0000000000000000000000000000ssss

        unsigned char stickyBit;

        // If all bits are zero it is 0, Otherwise it is 1
        if (stickyBits == 0x00)
        {
            stickyBit = 0x00;
        }
        else
        {
            stickyBit = 0x01;
        }

        switch (guardBits)
        {
            case 0x0:
                // truncate
                // 000000000XXXXXXXXXXXXXXXXXXXXXXX
                break;
            case 0x1:
                // truncate
                // 000000000XXXXXXXXXXXXXXXXXXXXXXX
                break;
            case 0x2:
                if (stickyBit == 0x0)
                {
                    // round to even
                    if ((in & 0x1) == 0x1)
                    {
                        // add one
                        significand += 1;
                    }
                }
                else
                {
                    // add one
                    significand += 1;
                }
                break;
            case 0x3:
                // add one
                significand += 1;
                break;
            default:
                break;
        }
    }

    // normal case
    // else
    // {
    //     significand = in & 0x7fffff;
    // }


    return significand;
}

// i2f
//   Parameter: 32-bit two's complement integer value.
//   Return value: 32-bit value that should be interpreted as an IEEE
//     single-precision floating-point value produced converting the
//     parameter to floating point.
//   Note: This routine should duplicate what the Intel 64 hardware
//     does when converting ints to floats.
uint32_t i2f(int32_t in)
{
    unsigned int sign = findSign(in);
    unsigned int exponent = findExponent(in);
    unsigned int significand = findSignificand(in);

    return (sign << 31) | (exponent << 23) | significand; // just a stub for now; always return all zero bits
}


// int main()
// {    

//     unsigned j = 0x3456789a;

//     j = 0x0000000f;

//     printf("j = %x\n\tBy hand: %x \n\tBy cast: %x\n", j, i2f(j), (int32_t) *(int32_t*)&j);
//     printf("sign: %x\nexponent: %x\nfraction: %x\n", i2f(j) >> 31, (i2f(j) << 1) >> 24, i2f(j) & 0x7ffff);

//     j = 0x345678A0;
//     printf("j = %x\n\tBy hand: %x \n\tBy cast: %x\n", j, i2f(j), (int32_t) *(int32_t*)&j);

//     j = 0x345678E0;
//     printf("j = %x\n\tBy hand: %x \n\tBy cast: %x\n", j, i2f(j), (int32_t) *(int32_t*)&j);

//     j = 0x345678A1;
//     printf("j = %x\n\tBy hand: %x \n\tBy cast: %x\n", j, i2f(j), (int32_t) *(int32_t*)&j);

//     j = 0x345678B0;
//     printf("j = %x\n\tBy hand: %x \n\tBy cast: %x\n", j, i2f(j), (int32_t) *(int32_t*)&j);

    

//     // // compare f2i output to floats casted to ints
//     // for (int i = -1048575; i < 1048575; i++)
//     // {
//     //     // show every conversion
//     //     printf("%x, %x\n", i2f(i), (int32_t) *(int32_t*)&i);
        
//     //     if(i2f(i) != (int32_t) *(float *)&i) 
//     //     {
//     //         printf("%x != %x\n", i2f(i), (int32_t) *(float *)&i);
//     //         assert(false);
//     //     }
//     // }

//     return 0;
// }
