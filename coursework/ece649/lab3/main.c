#include <msp430fr6989.h>
#define redLED BIT0 // Red LED at P1.0

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop the Watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // Enable the GPIO pins

    // Direct pin as output
    P1DIR = redLED;

    // Turn LED Off
    P1OUT &= ~redLED;

    TA0CCR0 = 0xffff;
    // Configure Channel 0 for up mode with interrupt
    // Enable Channel 0 CCIE bit
    TA0CCTL0 |= CCIE;

    // Clear Channel 0 CCIFG bit
    TA0CCTL0 &= ~CCIFG;

    // Timer_A: ACLK, divide by 2, up mode, clear TAR (leaves TAIE=0)
    TA0CTL = TASSEL_1 | ID_1 | MC_1 | TACLR;

    // Enable the global interrupt bit (call an intrinsic function)
    _BIS_SR(GIE);
}

//*******************************
#pragma vector = TIMER0_A0_VECTOR
__interrupt void T0A0_ISR()
{
    // Toggle the red LED
    P1OUT ^= redLED;

    // clears the flag (CCIFG in TA0CCTL0)
    TA0CCTL0 &= ~CCIFG;

    // Code for changing LED toggling frequency
    TA0CCR0 -= 0x2000;
}
