//
// f2i: convert IEEE single-precision floating-point to
// 32-bit two's complement integer.
//
// Remember when you implement the function you may not use the
// float or double types. Everything must be done using only integer
// types.

#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

// f2i
//   Parameter: 32-bit value that should be interpreted as an IEEE
//     single-precision floating-point value.
//   Return value: 32-bit two's complement integer value produced by
//     converting the parameter to integer.
//   Note: This routine should duplicate what the Intel 64 hardware
//     does when converting floats to ints. Be sure to consider NaNs,
//     denormalized numbers, infinities, overflow, etc.
int32_t f2i(uint32_t in)
{
    unsigned BIAS = 127;

    // pull out sign bit
    unsigned sign = in >> 31;

    // pull out exponent
    unsigned exponent = in >> 23 & 0xFF;

    // pull out fraction
    unsigned fraction = in & 0x7FFFFF;

    // Special cases: NaN and Infinity
    if (exponent == 0xFF)
    {
        //printf("NaN and Infinity\n");
        return 0x80000000;
    }

    // Denormalized values
    if (exponent == 0)
    {
        //printf("denormalized values\n");
        return 0;
    }

    // subtract stored value from BIAS to get actual exponent value
    int val = exponent - BIAS;

    // values less than one
    if (val < 0)
    {
        //printf("between -1 and 1\n");
        return 0;
    }

    // Overflow
    if (val > 30)
    {
        //printf("\toverflow\n");
        return 0x80000000;
    }

    // Start forming the returned value
    int x = 1 << val;

    // Depending on the exponent value...
    if (val < 23)
    {
        // discard decimal digits
        x |= fraction >> (23 - val);
    }
    else
    {
        // add trailing zeroes
        x |= fraction << (val - 23);
    }

    // if the sign bit is on
    if (sign == 1)
    {
        // make negative
        x = ~x + 1;
    }

    return x;
}
