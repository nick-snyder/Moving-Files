// ----------------------------------------------------------------------------
// myGpio.c  ('FR6989 Launchpad)
// ----------------------------------------------------------------------------

#include <driverlib.h>
#include "myGpioLab3.h"

#define RED_ON              0x0001      // Enable and turn on the red LED
#define RED_OFF             0xFFFE      // Turn off the red LED
#define GREEN_ON			0x0080		// Enable and turn on the green LED
#define GREEN_OFF			0xFF00		// Turn off the green LED
#define DEVELOPMENT         0x5A80      // Stop the watchdog timer
#define ENABLE_PINS         0xFFFE      // Required to use inputs and outputs
#define BUTTON1				0x0002		// P1.1 is button 1
#define BUTTON2				0x0004		// P1.2 is button 2


//*****************************************************************************
// Initialize GPIO
//*****************************************************************************
void initGPIO(void)
{
	P1DIR = RED_ON; 	        // Red LED pin will be an output

	P1OUT &= RED_OFF;           // Start with red LED off

    P9DIR &= ~(0x63);           // Green LED pin will be an output configuring 9.5, 9.6, 9.1, 9.0 as outputs for keypad 0110 0011
    P9REN = 0x63;               // 0110 0011
    P9OUT = 0x63;               // Start with green LED off

    P8DIR = 0xF0;               // Enabling port 8 pins as inputs
    P8REN = 0xF0;               // Set upper 4bits of port 8 as inputs with pulldown
    P8OUT = 0xF0;               // enable pull up/down resistor configuration for 8.7,8.6,8.5,8.4 1111 0000

    PM5CTL0 = ENABLE_PINS;      // Enable to turn on LEDs

	P1REN = 0x02; 				// Set P1.1 as input with pull-up
	P1OUT = 0x02; 				// enable pull up/down resistor configuration (for push button 1)

	P1REN |= 0x04;  			// Set P1.2 as input with pull-up
	P1OUT |= 0x04;  			// enable pull up/down resistor configuration (for push button 2)

    // Set LFXT (low freq crystal pins) to crystal input (rather than GPIO)
    GPIO_setAsPeripheralModuleFunctionInputPin(
            GPIO_PORT_PJ,
            GPIO_PIN4 +              	// LFXIN  on PJ.4
            GPIO_PIN5 ,             	// LFXOUT on PJ.5
            GPIO_PRIMARY_MODULE_FUNCTION
    );
}
