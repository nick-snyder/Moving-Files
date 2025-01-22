#include <msp430.h>

#define GREEN_ON    0x80
#define GREEN_OFF   0x7F
#define RED_ON      0x01
#define RED_OFF     0xFE
#define BUTTON11    0x02
#define BUTTON12    0x04

#define DEVELOPMENT 0x5A80
#define ENABLE_PINS 0xFFFE

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;

	P9DIR = GREEN_ON;
	P9REN = 0x00;
	P9OUT |= BIT7; //0x00;

    P1DIR = RED_ON;
    P1REN = BUTTON11 | BUTTON12;
    P1OUT = BUTTON11 | BUTTON12 | ~BIT0;


    // turn on green
    P9OUT |= GREEN_ON;

    // alternate between red and green for remainder
    while (1)
    {
        // if button 1 is pressed
        if (~P1IN & BUTTON11)
        {
            __delay_cycles(1000000);
        }

        // if button 2 is pressed
        else if (~P1IN & BUTTON12)
        {
            __delay_cycles(500000);
        }

        // normal state
        else
        {
            __delay_cycles(2000000);
        }

//        // turn off green
//        P9OUT = P9OUT ^ BIT7; //^= GREEN_ON;
//
//        // turn on red
//        P1OUT  = P1OUT ^ BIT0; //^= RED_ON;

        // flip green
        P9OUT ^= GREEN_ON;

        // flip red
        P1OUT ^= RED_ON;
    }
}
