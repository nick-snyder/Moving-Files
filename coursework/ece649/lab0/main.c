#include <msp430.h>

#define GREEN_ON    0x80
#define GREEN_OFF   0x7F
#define BUTTON12    0x04
#define DEVELOPMENT 0x5A80
#define ENABLE_PINS 0xFFFE

void main()
{
    WDTCTL = DEVELOPMENT; // Stop watchdog timer

    PM5CTL0 = ENABLE_PINS;

    P9DIR = GREEN_ON;

    P1OUT = BUTTON12;
    P1REN = BUTTON12;

    while (1)
    {
        if ((BUTTON12 & P1IN) == 0) // Button pressed
        {
            P9OUT |= GREEN_ON; // Turn on LED
        }
        else
        {
            P9OUT &= GREEN_OFF; // Turn off LED
        }
    }
}
