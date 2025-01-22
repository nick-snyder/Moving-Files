#include <msp430.h> 
#include "driverlib.h"
#include "myGpioLab3.h"
#include "myClocks.h"
#include "myLcdLab3.h"

#define redLED BIT0
#define greenLED BIT7
#define BUTTON11 BIT1
#define BUZZER BIT3

void config_clocks(void);
void welcome_message(void);
void countdown(void);
void play_music(void);
void play_note(char);

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5; // Enable the GPIO pins
	
	initGPIO();     // Required for the LCD ???
    initClocks();   // Required for the LCD
    myLCD_init();   // Required for the LCD

    // RED LED. P1.0
    P1DIR |= BIT1;  // Output
    P1REN &= ~BIT1; // Resistors disabled
    P1OUT &= ~BIT1; // Start low

    // BUTTON. P1.1
    P1DIR &= ~BIT1; // Input
    P1REN |= BIT1;  // Resistors enabled
    P1OUT &= ~BIT1; // Pull-up enabled
    P1SEL1 &= ~BIT1; // Primary selected
    P1SEL0 |= BIT1; // Primary selected
    P1IES &= ~BIT1; // Low-to-high transition
    P1IE |= BIT1;   // Port interrupt enabled
    P1IFG &= ~BIT1; // Clear interrupt

    // BUZZER. P1.3
    P1DIR |= BIT3;  // Output
    P1REN &= ~BIT3; // Resistors disabled
    P1OUT &= ~BIT3; // start low
    P1SEL1 &= ~BIT3; // GPIO selected
    P1SEL0 &= ~BIT3; // GPIO selected

    // GREEN LED. P9.7
    P9DIR |= BIT7;  // Output
    P9REN &= ~BIT7; // Resistors disabled
    P9OUT &= ~BIT7; // Start low

    // Enable the global interrupt bit (call an intrinsic function)
    _enable_interrupts();

	welcome_message();
//    countdown();
    config_clocks();
    play_music();

	return 0;
}

#pragma vector = PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
    P1IFG &= ~BIT1; // Clear interrupt

//    P1OUT ^= BUZZER | redLED;

    // start the countdown
    countdown();
}

//*******************************
#pragma vector = TIMER0_A0_VECTOR
__interrupt void T0A0_ISR()
{
    // clears the flag (CCIFG in TA0CCTL0)
    TA1CCTL0 &= ~CCIFG;

    P1OUT ^= BUZZER | redLED;

    P9OUT ^= greenLED;
}

void config_clocks()
{
//    TA1CCTL0 |= CCIE; // Enable Channel 0 CCIE bit
//    TA1CCTL0 &= ~CCIFG; // Clear Channel 0 CCIFG bit

    TA1CCR0 = 74; // 1 second period
    TA1CCR2 = TA0CCR0 / 2; // 50% duty

    TA1CCTL2 = OUTMOD_7; // set output mode to toggle

    // Timer_A: ACLK, divide by 1, up mode, clear TAR (leaves TAIE=0)
    TA1CTL = TASSEL_1 | ID_0 | MC_2 | TACLR;


}

void welcome_message()
{
    // while BUTTON is not pressed (BIT1 is LOW)
    while (1)
    {
        // show welcome message
        myLCD_showChar('P', 1);
        myLCD_showChar('R', 2);
        myLCD_showChar('E', 3);
        myLCD_showChar('S', 4);
        myLCD_showChar('S', 5);
        myLCD_showChar(' ', 6);

        __delay_cycles(5000000);

        myLCD_showChar('S', 1);
        myLCD_showChar('1', 2);
        myLCD_showChar(' ', 3);
        myLCD_showChar(' ', 4);
        myLCD_showChar(' ', 5);
        myLCD_showChar(' ', 6);

        __delay_cycles(5000000);
    }
}

void countdown()
{
    // clear LCD
    myLCD_showChar(' ', 1);
    myLCD_showChar(' ', 2);
    myLCD_showChar(' ', 3);
    myLCD_showChar(' ', 4);
    myLCD_showChar(' ', 5);
    myLCD_showChar(' ', 6);

    // count down from 3 to 1
    char c;
    int i;
    for (i = 3; i > 0; i--)
    {
        c = i + '0';    // cast int to char

        myLCD_showChar(c, 1);       // show count on LCD
        P1OUT |= BUZZER + redLED;   // turn on buzzer and LED
        __delay_cycles(3000000);    // wait

        myLCD_showChar(' ', 1);     // clear LCD
        P1OUT &= ~BUZZER & ~redLED; // turn off buzzer and LED
        __delay_cycles(3000000);    // wait
    }

//    myLCD_showChar(' ', 1);
}

void play_music()
{
    // music plays
    // musical note is a PWM signal at 50% duty and at some period

    /**
     * half     2       16384
     *
     * quarter  4       8192
     *
     * 0    a        440     74
     * 1    b flat   466     70
     * 3    b        494     66
     * 4    c        523     63
     * 5    c sharp  554     59
     * 6    d        587     56
     * 7    e flat   622     53
     * 8    e        659     50
     * 9    f        698     47
     * 10   f sharp  740     44
     * 11   g        784     42
     * 12   a flat   831     39
     * 13   a        880     37
     */

    // EDC, EDC, FED, FED
    play_note('e');
    play_note('d');
    play_note('c');

    __delay_cycles(2000000);

    play_note('e');
    play_note('d');
    play_note('c');

    __delay_cycles(2000000);

    play_note('f');
    play_note('e');
    play_note('d');

    __delay_cycles(2000000);

    play_note('f');
    play_note('e');
    play_note('d');
}

void play_note(char note)
{
    myLCD_showChar(' ', 1);
    myLCD_showChar(' ', 2);

    switch (note)
    {
        case 'a':
            TA1CCR0 = 74;
            TA1CCR2 = TA0CCR0 / 2;
            myLCD_showChar('A', 1);
            break;
        case 'x':
            TA1CCR0 = 70;
            TA1CCR2 = TA0CCR0 / 2;
            myLCD_showChar('A', 1);
            myLCD_showChar('b', 2);
            break;
        case 'b':
            TA1CCR0 = 66;
            TA1CCR2 = TA0CCR0 / 2;
            myLCD_showChar('B', 1);
            break;
        case 'c':
            TA1CCR0 = 63;
            TA1CCR2 = TA0CCR0 / 2;
            myLCD_showChar('C', 1);
            break;
        case 'z':
            TA1CCR0 = 59;
            TA1CCR2 = TA0CCR0 / 2;
            myLCD_showChar('C', 1);
            myLCD_showChar('#', 2);
            break;
        case 'd':
            TA1CCR0 = 56;
            TA1CCR2 = TA0CCR0 / 2;
            myLCD_showChar('D', 1);
            break;
        case 'v':
            TA1CCR0 = 53;
            TA1CCR2 = TA0CCR0 / 2;
            myLCD_showChar('E', 1);
            myLCD_showChar('b', 2);
            break;
        case 'e':
            TA1CCR0 = 50;
            TA1CCR2 = TA0CCR0 / 2;
            myLCD_showChar('E', 1);
            break;
        case 'f':
            TA1CCR0 = 47;
            TA1CCR2 = TA0CCR0 / 2;
            myLCD_showChar('F', 1);
            break;
        case 'w':
            TA1CCR0 = 44;
            TA1CCR2 = TA0CCR0 / 2;
            myLCD_showChar('F', 1);
            myLCD_showChar('#', 2);
            break;
        case 'g':
            TA1CCR0 = 42;
            TA1CCR2 = TA0CCR0 / 2;
            myLCD_showChar('G', 1);
            break;
        case 'y':
            TA1CCR0 = 39;
            TA1CCR2 = TA0CCR0 / 2;
            myLCD_showChar('A', 1);
            myLCD_showChar('b', 2);
            break;
        case 'p':
            TA1CCR0 = 37;
            TA1CCR2 = TA0CCR0 / 2;
            myLCD_showChar('A', 1);
            break;
        default:
            break;
    }

    TA1CCR2 = TA1CCR0 / 2;
    __delay_cycles(2000000);
}
