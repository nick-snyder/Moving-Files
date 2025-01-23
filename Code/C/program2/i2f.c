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
#include <stdbool.h>

// i2f
//   Parameter: 32-bit two's complement integer value.
//   Return value: 32-bit value that should be interpreted as an IEEE
//     single-precision floating-point value produced converting the
//     parameter to floating point.
//   Note: This routine should duplicate what the Intel 64 hardware
//     does when converting ints to floats.
uint32_t i2f(int32_t in)
{
    // find the sign
    bool sign = in >> 31;

    // convert from two's complement
    if (in >> 31)
    {
        in = (~in) + 1;
    }

    // find the exponent
    unsigned char exponent = 0x00;
    int shift = 0;
    for (shift = 1; shift <= 32; shift++)
    {
        // slide the int all the way to the left (>> 32) and each iteration slide back by one less (>> 32 - i)
        // iterate until end of int or until observed bit is not same as the sign bit
        if ((in >> (32 - shift)) == 0x1)
        {
            exponent = 32 - shift + 127;
            break;
        }
    }

    // find fraction/significand
    // pull out first 23 bits after shift
    unsigned int significand = ((in << shift) & 0xfffffe00) >> 9;
    // unsigned int significand = 0;

    // if there are extra bits after the significand
    if (shift < (32 - 23))
    {
        // pull out the extra bits
        unsigned int extraBits = ((unsigned int) in) << (23 + shift) >> (23 + shift);

        // the 2 MSBs are always the guard bits
        unsigned int guardBits = ((extraBits << (23 + shift)) & 0xc0000000) >> 30;

        // the rest of the extra bits are the sticky bits
        unsigned int stickyBits = ((extraBits << (23 + shift + 2)) & 0xff800000) >> (23 + shift);

        // If all bits are zero it is 0, Otherwise it is 1
        bool stickyBit = 0;
        if (stickyBits == 0x0)
        {
            stickyBit = 0x0;
        }
        else
        {
            stickyBit = 0x1;
        }

        // determine whether to round or truncate
        if (guardBits == 0x2)
        {
            if (stickyBit == 0x0)
            {
                // add one if odd
                if ((significand & 0x1) == 0x1)
                {
                    // if overflow
                    if (significand == 0x7fffff)
                    {
                        // overflow to exponent
                        exponent++;
                    }

                    significand++;
                }
            }
            else
            {
                // if overflow
                if (significand == 0x7fffff)
                {
                    // overflow to exponent
                    exponent++;
                }
                
                significand++;
            }
        }
        else if (guardBits == 0x3)
        {
            // if overflow
            if (significand == 0x7fffff)
            {
                // overflow to exponent
                exponent++;
            }
            
            significand++;
        }
        // all other cases truncate
    }

    // arrange each part into the return value
    return (sign << 31) | (exponent << 23) | significand;
}


// int main()
// {    

//     unsigned int j;

//     j = 0x01000003;
//     // printf("j = %x\n\tBy hand: %x \n\tBy cast: %x\n", j, i2f(j), (int32_t) *(int32_t*)&j);
//     printf("value: %x\n\tsign: %x\n\texponent: %x\n\tfraction: %x\n", i2f(j), i2f(j) >> 31, (i2f(j) << 1) >> 24, i2f(j) & 0x7ffff);

//     j = 0x7fffffc1;
//     // printf("j = %x\n\tBy hand: %x \n\tBy cast: %x\n", j, i2f(j), (int32_t) *(int32_t*)&j);
//     printf("value: %x\n\tsign: %x\n\texponent: %x\n\tfraction: %x\n", i2f(j), i2f(j) >> 31, (i2f(j) << 1) >> 24, i2f(j) & 0x7ffff);

//     j = 0x7fffffff;
//     // printf("j = %x\n\tBy hand: %x \n\tBy cast: %x\n", j, i2f(j), (int32_t) *(int32_t*)&j);
//     printf("value: %x\n\tsign: %x\n\texponent: %x\n\tfraction: %x\n", i2f(j), i2f(j) >> 31, (i2f(j) << 1) >> 24, i2f(j) & 0x7ffff);

//     j = 0xffffffff;
//     // printf("j = %x\n\tBy hand: %x \n\tBy cast: %x\n", j, i2f(j), (int32_t) *(int32_t*)&j);
//     printf("value: %x\n\tsign: %x\n\texponent: %x\n\tfraction: %x\n", i2f(j), i2f(j) >> 31, (i2f(j) << 1) >> 24, i2f(j) & 0x7ffff);

//     j = 0x00000001;
//     // printf("j = %x\n\tBy hand: %x \n\tBy cast: %x\n", j, i2f(j), (int32_t) *(int32_t*)&j);
//     printf("value: %x\n\tsign: %x\n\texponent: %x\n\tfraction: %x\n", i2f(j), i2f(j) >> 31, (i2f(j) << 1) >> 24, i2f(j) & 0x7ffff);


    

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
