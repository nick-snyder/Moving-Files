#include <msp430.h> 
#include <driverlib.h> // Required for the LCD
#include "myGpioLab3.h" // Required for the LCD
#include "myClocks.h" // Required for the LCD
#include "myLcdLab3.h" // Required for the LCD
//Note, myLcd.c file has been changed to display * and #
//myGpio.c file has been changed as well, to configure the port direction, pull-down resistor, and input/outport pins

/*
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    initGPIO(); // Initializes General Purpose
    // Inputs and Outputs for LCD
    initClocks(); // Initialize clocks for LCD
    myLCD_init(); // Prepares LCD to receive commands

    int i = 0;

    while(1)
    {
        // if button 1 is pressed
        if (~P1IN & 0x02)
        {
            myLCD_showChar('N', 1);
            myLCD_showChar('I', 2);
            myLCD_showChar('C', 3);
            myLCD_showChar('K', 4);

            while (1)
            {
                // if button 2 is pressed
                if (~P1IN & 0x04)
                {
                    break;
                }

                __delay_cycles(10000000);
                break;
            }

            myLCD_showChar(' ', 1);
            myLCD_showChar(' ', 2);
            myLCD_showChar(' ', 3);
            myLCD_showChar(' ', 4);
        }

        switch(i)
        {
            case 0:
                P8OUT &= ~BIT7;

                while (~P9IN & BIT0)
                {
                    myLCD_showChar( '*', 3 );
                }
                while (~P9IN & BIT1)
                {
                    myLCD_showChar( '7', 3 );
                }
                while (~P9IN & BIT5)
                {
                    myLCD_showChar( '4', 3 );
                }
                while (~P9IN & BIT6)
                {
                    myLCD_showChar( '1', 3 );
                }

                P8OUT |= BIT7;
                i++;
                break;

            case 1:
                P8OUT &= ~BIT6;

                while (~P9IN & BIT0)
                {
                    myLCD_showChar( '0', 3 );
                }
                while (~P9IN & BIT1)
                {
                    myLCD_showChar( '8', 3 );
                }
                while (~P9IN & BIT5)
                {
                    myLCD_showChar( '5', 3 );
                }
                while (~P9IN & BIT6)
                {
                    myLCD_showChar( '2', 3 );
                }

                P8OUT |= BIT6;
                i++;
                break;

            case 2:
                P8OUT &= ~BIT5;

                while (~P9IN & BIT0)
                {
                    myLCD_showChar( '#', 3 );
                }
                while (~P9IN & BIT1)
                {
                    myLCD_showChar( '9', 3 );
                }
                while (~P9IN & BIT5)
                {
                    myLCD_showChar( '6', 3 );
                }
                while (~P9IN & BIT6)
                {
                    myLCD_showChar( '3', 3 );
                }

                P8OUT |= BIT5;
                i++;
                break;

            case 3:
                P8OUT &= ~BIT4;

                while (~P9IN & BIT0)
                {
                    myLCD_showChar( 'D', 3 );
                }
                while (~P9IN & BIT1)
                {
                    myLCD_showChar( 'C', 3 );
                }
                while (~P9IN & BIT5)
                {
                    myLCD_showChar( 'B', 3 );
                }
                while (~P9IN & BIT6)
                {
                    myLCD_showChar( 'A', 3 );
                }

                P8OUT |= BIT4;
                i = 0;
                break;
        }
    }
}
