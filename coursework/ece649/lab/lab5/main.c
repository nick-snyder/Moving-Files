#include <msp430fr6989.h>

#define BUTTON11 BIT1 // P1.1 input
#define redLED BIT0 // P1.0 output
#define greenLED BIT7 // P9.7 output

// array of characters to set the UCA0TXBUF
unsigned char val[10] = {0x24, 0x41, 0x42, 0x96, 0xFE, 0x78, 0x12, 0x95, 0x65, 0x96};
// counter that accesses each index of the char array
unsigned int index;

void assign_UART_pins(); // configuring UART
void select_clock_signals(); // configuring clock source
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5; // Enable the GPIO pins

	assign_UART_pins(); // configuring UART communications
	select_clock_signals(); // configuring clock source

    // configure red and green LEDs and pushbutton
	P1DIR = redLED; // red LED P1.0 is output
	P1OUT &= ~redLED; // turn off red LED
	P9DIR = greenLED; // green LED P9.7 is output

	// BUTTON. P1.1
    P1DIR &= ~BIT1; // Input
    P1REN |= BIT1;  // Resistors enabled
    P1OUT &= ~BIT1; // Pull-up enabled
    P1SEL1 &= ~BIT1; // Primary selected
    P1SEL0 |= BIT1; // Primary selected
    P1IES |= BIT1; // high-to-low transition
    P1IE |= BIT1;   // Port interrupt enabled
    P1IFG &= ~BIT1; // Clear interrupt

	index = 0; // initialize counter

	//configure the timer to send characters to receiver at different times
    TA0CCR0 = 32768-1; // Set CCR0 for up mode to 32767
    TA0CCTL0 |= CCIE; // Enable Channel 0 CCIE bit
    TA0CCTL0 &= ~CCIFG; // Clear Channel 0 CCIFG bit

    // Timer_A: ACLK, div by 2, up mode, clear TAR (leaves TAIE=0)
    TA0CTL = TASSEL_1 | ID_1 | MC_1 | TACLR;

	// enable global interrupt to call intrinsic functions
    _BIS_SR(GIE);

    // initialize transmitter buffer (setting to 0x96 as test)
    UCA0TXBUF = 0x96;
    UCA0CTLW0 &= UCSWRST;

    // continue program
    while(1){
       
    }

}

////UART interrupt
#pragma vector=USCI_A0_VECTOR
__interrupt void UART_ISR(void) {
    // acknowledging if transmit is complete
    if (UCA0TXBUF == 0) { // check if the transmit complete? -> transmit buffer is empty

        if (UCA0RXBUF == 0x96) { //check if 0x96 is arrived in the buffer
            // red LED on
            P1OUT |= redLED;

            // green LED off
            P9OUT &= ~greenLED;

        } else {
             // red LED off
            P1OUT &= ~redLED;

            // green LED on
            P9OUT |= greenLED;
        }
    }

    // Clear TX Complete Interrupt Flag in UCA0IFG register
    UCA0IFG &= ~UCTXCPTIFG;

     // enable transmitter interrupt again as precaution
    UCA0IE = UCTXCPTIE; // enable transmit complete interrupt

}


#pragma vector = PORT1_VECTOR
__interrupt void myISR() {
    if (P1IFG & BUTTON11) { // check to see if P1IFG was set
        __delay_cycles(500000); // debounce delay
        if ((P1IN & BUTTON11) == 0) {   // check again after debounce
            WDTCTL ^= (WDTPW | WDTHOLD); // toggle current state of the watchdog timer
        }
        P1IFG &= ~BUTTON11;  // clear interrupt flag for Button11
    }
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void T0A0_ISR() {
    //
    UCA0TXBUF = val[index]; // set new character to the transmitter buffer
    index++; // increment the index counter to be prepared to send the next character in the array

    if (index > 9) { // if the index has reached a value passed 9, reset index to point back to beginning of array
        index = 0;
    }

    // Hardware clears the flag (CCIFG in TA0CCTL0)
    TA0CCTL0 &= ~CCIFG;

    // Code for changing LED toggling frequency
    TA0CCR0 /= 2; // divides the CCR0 value in half
    if (TA0CCR0 < 800) { // check to see if it reaches a specific minimum before resetting to original max
        TA0CCR0 = 32768 - 1;
    }

}

// configuring UART pins
void assign_UART_pins() {
    // configuring UART pins to be TX (P4.2) and RX (P4.3)
    
    P4SEL1 &= BIT3 | BIT2; // bit 2 and 3 are logic 0
    P4SEL0 |= ~(BIT3 | BIT2); // bit 2 and 3 are logic 1

//    P4DIR = BIT2;
//    P4REN = BIT3;
//    P4OUT = BIT2;

    //P4OUT &= BIT3; // bit 2 and 3 are logic 0
    //P4OUT &= // bit 2 and 3 are logic 1

    // using SMCLK
    UCA1CTLW0 |= UCSSEL_2;
    
    // baud word rate
    // configure modulation control register
    // for 9600 baud rate, UCBR = 6, UCBRF = 13, UCBRS = 0x22, UCOS16 = 1
    UCA1BRW = 6;
    UCBR1 = 6;
    UCBRF1 = 13;
    UCBRS1 = 0x22;
    UCOS16 = 0x01;
    UCA1MCTLW = UCBRS5 | UCBRS1 | UCBRF3 | UCBRF2 | UCBRF0 | UCOS16;

    // exit reset state
    UCA0CTLW0 &= ~UCSWRST;

    UCA0IE = UCTXCPTIE; // enable transmit complete interrupt
}

// configuring clock signals
void select_clock_signals() {
    CSCTL0 = CSKEY; //provide password to access clock calibration registers
    CSCTL1 = DCOFSEL_0; // 1MHz

    CSCTL2 = SELM1 | SELM0 | SELS1| SELS0 | SELA0; // ACLK and MCLK are very low power and frequency oscillators
    // and SMCLK is digitally controlled oscillator
    CSCTL3 = 0x0000; // do not slow down frequency of clocks
    FRCTL0 = FRCTLPW | NWAITS0; // PREVENTS FRAM FROM MCLK > 8MHz
}

