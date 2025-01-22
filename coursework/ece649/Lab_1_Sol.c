#include <msp430.h> 


// Declare function used in main. Definition is below.
void delay_function(int delay_time);

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // low power mode

    // Set LED1 (P1.0) and LED (P9.7) as output
    P1DIR |= BIT0;
    P9DIR |= BIT7;

    // Set P1.1 and P1.2 as input
    P1DIR &= ~(BIT1 | BIT2);
    // Enable pull up/down resistor
    P1REN = (BIT1 | BIT2);
    // Set pull up resistor on buttons and turn on LED 1
    P1OUT = (BIT1 | BIT2 | ~BIT0);
    // Turn on LED 2
    P9OUT |= BIT7;

    // Check for inputs indefinitely
    while (1) {

        // Wait desired time
        // int d_time; // can use this but it takes up more RAM

        // If button 1 is pressed
        if (~P1IN & BIT1) {
            delay_function(1); // Wait 1 second
        } else if (~P1IN & BIT2) { // If button 2 is pressed
            delay_function(0); // Wait 0.5 seconds
        } else { // If not button is pressed
            delay_function(2); // Wait 2 seconds
        }

        // Alternate LED 1
        P1OUT = P1OUT ^ BIT0;
        // Alternate LED 2
        P9OUT = P9OUT ^ BIT7;

    }
}

// This function takes an int as a parameter and calls __delay_cycles with the appropriate value.
// int delay_time: 2 = 2s, 1 = 1s, 0 = 0.5s
void delay_function(int delay_time) {

    if (delay_time == 2) { // if parameter is 2
        __delay_cycles(2000000); // Wait 2000000 clock cycles (1Mhz clock), 2s
    } else if (delay_time == 1) { // if parameter is 1
        __delay_cycles(1000000); // Wait 1000000 clock cycles (1Mhz clock), 1s
    } else if (delay_time == 0) { // if parameter is 0
        __delay_cycles(500000); // Wait 500000 clock cycles (1Mhz clock). 0.5s
    } else { // Handle any exception with default case
        __delay_cycles(2000000); // Wait 2000000 clock cycles (1Mhz clock)
    }

}
