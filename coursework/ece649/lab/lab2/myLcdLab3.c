// ----------------------------------------------------------------------------
// myLCD.c  ('FR6989 LaunchPad)
// ----------------------------------------------------------------------------

// ***** Header Files *********************************************************
#include "myLcdLab3.h"
#include "string.h"
#include "driverlib.h"


// ***** Prototypes ***********************************************************
// See additional prototypes in the 'myLCD.h' file
void TEST_myLCD_showSymbol( void );


// ***** Global Variables******************************************************
// Memory locations for LCD characters
const uint8_t SegmentLoc[ LCD_NUM_CHAR ][ 4 ] =
{
        { 18, 19, 20, 21 },                                                     // Position 1 = Digit A1
        { 10, 11, 12, 13 },                                                     // Position 2 = Digit A2
        {  6,  7,  8,  9 },                                                     // Position 3 = Digit A3
        { 36, 37, 38, 39 },                                                     // Position 4 = Digit A4
        { 28, 29, 30, 31 },                                                     // Position 5 = Digit A5
        { 14, 15, 16, 17 }                                                      // Position 6 = Digit A6
};

// LCD memory map for numeric digits
const char digit[10][2] =
{
    {0xFC, 0x28},  /* "0" LCD segments*/
    {0x60, 0x20},  /* "1" */
    {0xDB, 0x00},  /* "2" */
    {0xF1, 0x00},  /* "3" */
    {0x67, 0x00},  /* "4" */
    {0xB7, 0x00},  /* "5" */
    {0xBF, 0x00},  /* "6" */ // 1011 1111
    {0xE0, 0x00},  /* "7" */ // 1110 0000
    {0xFF, 0x00},  /* "8" */ // 1111 1111
    {0xF7, 0x00}   /* "9" */ // 1111 0111
};

// LCD memory map for uppercase letters
const char alphabetBig[26][2] =
{
    {0xEF, 0x00},  /* "A" LCD segments*/
    {0xF1, 0x50},  /* "B" */
    {0x9C, 0x00},  /* "C" */
    {0xF0, 0x50},  /* "D" */ // 1111 0000 0101 0000
    {0x9E, 0x00},  /* "E" */ // 1001 1110 0000 0000
    {0x8E, 0x00},  /* "F" */ // 1000 1110 0000 0000
    {0xBD, 0x00},  /* "G" */ // 1011 1101 0000 0000
    {0x6F, 0x00},  /* "H" */
    {0x90, 0x50},  /* "I" */
    {0x78, 0x00},  /* "J" */
    {0x0E, 0x22},  /* "K" */
    {0x1C, 0x00},  /* "L" */
    {0x6C, 0xA0},  /* "M" */ // 0110 1100 1010 0000
    {0x6C, 0x82},  /* "N" */ // 0110 1100 1000 0010
    {0xFC, 0x00},  /* "O" */ // 1111 1100 0000 0000
    {0xCF, 0x00},  /* "P" */
    {0xFC, 0x02},  /* "Q" */
    {0xCF, 0x02},  /* "R" */
    {0xB7, 0x00},  /* "S" */
    {0x80, 0x50},  /* "T" */
    {0x7C, 0x00},  /* "U" */
    {0x0C, 0x28},  /* "V" */
    {0x6C, 0x0A},  /* "W" */
    {0x00, 0xAA},  /* "X" */ // 0000 0000 1010 1010
    {0x00, 0xB0},  /* "Y" */ // 0000 0000 1011 0000
    {0x90, 0x28},  /* "Z" */ // 1001 0000 0010 1000
};
 const char star[1][2]={
	 {0x03, 0xAA}
 };
 const char hash[1][2]={
 	 {0xFF, 0x50}
  };
// This structure is defined by the LCD_C DriverLib module, and is passed to the LCD_C_init() function
LCD_C_initParam initParams = {
    LCD_C_CLOCKSOURCE_ACLK,                                                     // Use ACLK as the LCD's clock source
    LCD_C_CLOCKDIVIDER_1,
    LCD_C_CLOCKPRESCALAR_16,
    LCD_C_4_MUX,                                                                // LaunchPad LCD specifies 4MUX mode
    LCD_C_LOW_POWER_WAVEFORMS,
    LCD_C_SEGMENTS_ENABLED
};


//*****************************************************************************
// myLCD_init()
//
// Configures the LCD display controller, and then clears the display and
// enables it
//*****************************************************************************
void myLCD_init()
{
    // Turn off LCD
    LCD_C_off( LCD_C_BASE );

    // L0~L26 & L36~L39 pins selected for use with LCD
    // Note: LCD pin configurations override any GPIO settings for these pins
    LCD_C_setPinAsLCDFunctionEx( LCD_C_BASE,                                    // Gives range of pins to LCD controller
            LCD_C_SEGMENT_LINE_0,                                               // Starting Lx pin of range
            LCD_C_SEGMENT_LINE_21                                               // Ending pin of range
    );

    LCD_C_setPinAsLCDFunctionEx( LCD_C_BASE,                                    // Gives range of pins to LCD controller
            LCD_C_SEGMENT_LINE_26,                                              // Starting Lx pin of range
            LCD_C_SEGMENT_LINE_43                                               // Ending pin of range
    );

    // Init LCD as 4-mux mode
    LCD_C_init( LCD_C_BASE, &initParams );

    // LCD Operation - VLCD generated internally, V2-V4 generated internally, v5 to ground
    LCD_C_setVLCDSource( LCD_C_BASE, LCD_C_VLCD_GENERATED_INTERNALLY,
                         LCD_C_V2V3V4_GENERATED_INTERNALLY_NOT_SWITCHED_TO_PINS,
                         LCD_C_V5_VSS );

    // Set VLCD voltage
    LCD_C_setVLCDVoltage( LCD_C_BASE,
                          LCD_C_CHARGEPUMP_VOLTAGE_3_02V_OR_2_52VREF );

    // Enable charge pump and select internal reference for it
    LCD_C_enableChargePump( LCD_C_BASE );
    LCD_C_selectChargePumpReference( LCD_C_BASE,
                                     LCD_C_INTERNAL_REFERENCE_VOLTAGE );

    LCD_C_configChargePump( LCD_C_BASE, LCD_C_SYNCHRONIZATION_ENABLED, 0 );

    // Clear LCD memory
    LCD_C_clearMemory( LCD_C_BASE );
    LCD_C_clearBlinkingMemory( LCD_C_BASE );

    // Select to display main LCD memory
    LCD_C_selectDisplayMemory( LCD_C_BASE, LCD_C_DISPLAYSOURCE_MEMORY );

    // Turn blinking features off
    LCD_C_setBlinkingControl( LCD_C_BASE, LCDBLKPRE1, LCDBLKPRE2, LCD_C_BLINK_MODE_DISABLED );

    // Turn on LCD
    LCD_C_on( LCD_C_BASE );

// ----------------------------------------------------------------------------
// Test Routines
// ----------------------------------------------------------------------------
    //Runs the routine which tests all the options for the myLCD_showSymbol() function
    //TEST_myLCD_showSymbol();

    // Test other functions
    //myLCD_showChar( 'A', 1 );
    //myLCD_showChar( 'B', 2 );
    //myLCD_showChar( 'C', 3 );
    //myLCD_showChar( 'D', 4 );
    //myLCD_showChar( 'E', 5 );
    //myLCD_showChar( 'F', 6 );                                                 // Display should show "ABCDEF"

    //myLCD_displayNumber( 123456 );                                            // Display should show "123456"
    //myLCD_displayNumber( 1111111 );                                           // Display should show " ERROR"
}


//*****************************************************************************
// myLCD_showChar()
//
// Displays input character at given LCD digit/position
// Only spaces, numeric digits, and uppercase letters are accepted characters
//
// This function has two arguments and does not return a value.
//
// Arg 1: "c" is a string char that you want displayed on the LCD glass.
//        Currently, only A-Z and 0-9 and a space " " are supported. You can
//        clear any character position by using the space.
// Arg 2: "Position" tells the function where you want the character to be
//        placed. With six character positions, they're specified in this
//        order:  1 2 3 4 5 6
//
// This routine converts the provided string character to an offset into a
// lookup table, which provides the values to turn each character's
// segments on/off.
//
// The Position number is used to lookup locations for each nibble that
// controls a segment pin. Four nibbles are required per character.
//
// This routine uses the native LCD_C DriverLib "setMemory" functions. The
// LCD_C version of this routine only programs a nibble at a time, as opposed
// to the LCD_E_setMemory(), which programs the entire 8-bit LCDMEM register.
// See the examples found later in this file for an example which is closer
// to the LCD_E method. We called our example: myLCD_setMemoryBits().
//*****************************************************************************
void myLCD_showChar( char c, int Position )
{
    Position -= 1;

    if ( ( Position >= 0 ) && ( Position <= 6 ) )
    {

        if ( c == ' ' )
        {
            // Display space
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][0], 0 );
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][1], 0 );
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][2], 0 );
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][3], 0 );
        }
        else if ( c >= '0' && c <= '9' )
        {
            // Display digit
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][0], digit[c-48][0] ); //refer to ASCII Table
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][1], digit[c-48][0] >> 4 );
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][2], digit[c-48][1] );
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][3], digit[c-48][1] >> 4 );
        }
        else if ( c >= 'A' && c <= 'Z' )
        {
            // Display alphabet
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][0], alphabetBig[c-65][0] );
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][1], alphabetBig[c-65][0] >> 4 );
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][2], alphabetBig[c-65][1] );
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][3], alphabetBig[c-65][1] >> 4 );
        }
        else if (c == '*')
        {
            // Turn all segments on if character is not a space, digit, or uppercase letter
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][0], star[c-42][0]);
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][1], star[c-42][0] >> 4);
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][2], star[c-42][1] );
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][3], star[c-42][1]>>4 );
        }
		 else if (c == '#')
        {
                  // Turn all segments on if character is not a space, digit, or uppercase letter
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][0], hash[c-35][0]);
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][1], hash[c-35][0] >> 4);
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][2], hash[c-35][1] );
            LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][3], hash[c-35][1]>>4 );
        }
        else
               {
                   // Turn all segments on if character is not a space, digit, or uppercase letter
                   LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][0], 0xFF );
                   LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][1], 0xFF );
                   LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][2], 0xFF );
                   LCD_C_setMemory( LCD_C_BASE, SegmentLoc[Position][3], 0xFF );
               }
    }
}

//*****************************************************************************
// myLCD_displayNumber()
//
// Displays a right-aligned number on the display. This function takes one
// input value and does not return a value.
//
// Arg 1: "val" is the integer to be displayed. It must be less than 6 digits
//        in length or this function writes "ERROR". The number is first
//        converted into character equivalants, then displayed.
//
// This function does not provide any 'punctuation'. That is, decimals, signs
// or colons. You could add these using the myLCD_showSymbol() function.
//*****************************************************************************
void myLCD_displayNumber( unsigned long val )
{
    unsigned long div[6];
    unsigned long mod[6];
    unsigned long err;

    err = val / 1000000;
    if ( err > 0 )
    {
        myLCD_showChar( ' ', 1 );
        myLCD_showChar( 'E', 2 );
        myLCD_showChar( 'R', 3 );
        myLCD_showChar( 'R', 4 );
        myLCD_showChar( 'O', 5 );
        myLCD_showChar( 'R', 6 );
    }
    else
    {
        div[0] = val / 100000  ;
        mod[0] = val % 100000  ;
        div[1] = mod[0] / 10000;
        mod[1] = mod[0] % 10000;
        div[2] = mod[1] / 1000 ;
        mod[2] = mod[1] % 1000 ;
        div[3] = mod[2] / 100  ;
        mod[3] = mod[2] % 100  ;
        div[4] = mod[3] / 10   ;
        div[5] = mod[3] % 10   ;

        int i = 0;
        int LeadingZeros = 0;

        for ( i = 0; i < ( LCD_NUM_CHAR - 1); i++ )
        {
            if ( ( div[i] == 0 ) && ( !LeadingZeros ) )
            {
                myLCD_showChar( ' ', i + 1 );
            }
            else
            {
                myLCD_showChar( div[i] + '0', i + 1 );
                LeadingZeros++;
            }
        }

        i = LCD_NUM_CHAR - 1;
        myLCD_showChar( div[i] + '0', i + 1 );
    }
}

//*****************************************************************************
// TEST_myLCD_showSymbol()
//
// Provides a single function which tests every mode of the myLCD_showSymbol()
// function. You should be able to verify it's correct operation using with
// this function - along with use of breakpoints, single-stepping and a little
// manipulation of the LCD memory in the CCS Registers window.
//*****************************************************************************
void TEST_myLCD_showSymbol( void )
{
    int i;                                                                      // Iterates thru Operations
    int j;                                                                      // Iterates thru Symbols
    int m;                                                                      // Iterates thru Memories
    volatile int r = -1;                                                        // Let's you view the return value (volatile needed to compiler won't optimize it away)

    for ( m = 0; m < 2; m++ )
    {
        if ( m == 1 )
        {
            LCD_C_selectDisplayMemory( LCD_C_BASE, LCD_C_DISPLAYSOURCE_BLINKINGMEMORY );
        }
        else
        {
            LCD_C_selectDisplayMemory( LCD_C_BASE, LCD_C_DISPLAYSOURCE_MEMORY );
        }

        for ( i = 0; i <= 3; i++ )
        {
            for ( j = 0; j <= LCD_A4COL; j++ )
            {
                r = myLCD_showSymbol( i, j, m );
            }
        }
    }

    // Clear LCD memory and restore to display to main LCD memory
    LCD_C_selectDisplayMemory( LCD_C_BASE, LCD_C_DISPLAYSOURCE_MEMORY );
    LCD_C_clearMemory( LCD_C_BASE );
    LCD_C_clearBlinkingMemory( LCD_C_BASE );
}

//*****************************************************************************
// myLCD_showSymbol()
//
// The function shows (or modifies) the LCD memory bits to control the various
// special icons (i.e. non-character segments) of the display.
//
// This function has three arguments and returns either '0' or '1'.
//
//      Return - reflects the value of the icon's segment enable bit
//               at the end of the function
//      Arg 1  - 'Operation' specifies on of 4 different functions
//               that can be performed on an icon
//      Arg 2  - 'Symbol' indicates the special icon segment operated upon
//      Arg 3  - 'Memory' specifies which LCD memory (main or blinking)
//               the function should modify or test
//
// Operation:    The function can perform 4 different functions on each icon:
//
//      LCD_UPDATE - sets the segment bit to enable the icon
//      LCD_CLEAR  - clears the icon's segment bit
//      LCD_TOGGLE - toggles the icon's segment bit
//      LCD_GET    - returns the value of the icon's segment bit
//
//      Additionally, all operations return the icon's segment bit value.
//      For UPDATE, this should always be '1'; and for CLEAR, this should
//      be '0'; the others will vary based on the current value (GET) or
//      new value (TOGGLE).
//
//  Symbol:      The 'icon' value is used to select which LCD memory register
//               and bit to operate upon.
//
//  Memory:      Determines which LCD memory to act upon. '0'
//               represents the Main LCD memory registers; while '1' represents
//               the Blinking LCD memory registers. This allows a single
//               function to perform all the possible operations for a segment.
//
// The associated header file enumerates these operations as well as the various
// icons found on this LCD.
//*****************************************************************************
int myLCD_showSymbol( int Operation, int Symbol, int Memory )
{
    int idx = 0;                                                                // Specifies the index of the LCD memory register (i.e. x in LCDMx)
    int bit = 0;                                                                // Specifies the charachters bit within the LCD memory register
    int mem = 0;                                                                // Offset for LCD's "main" or "blinking" memory registers (either 0 or 32)
    int ret = -1;                                                               // Holds the function's return value

    // Which Memory has the user specified?  'Main' or 'Blinking'
    // Since 'Blinking' only applies to MUX4 (and lower) configurations, we ignore the Memory field if it does not apply.
    // This function cheats - instead of using LCDMx (for main) or LCDBMx (for blinking), we cheated and made use of the fact that the
    // two sets of LCD memory registers are aliased. Therefore, setting LCDBM3 also sets LCDM35.
    // Note, we made 'initParams' a global variable to make this test easier; though, we could have also tested the LCD register itself.
    if (( initParams.muxRate <= LCD_C_4_MUX ) && ( Memory == 1 ))
        mem = 35-3;                                                             // Writing to LCDBM35 also sets LCDM3 (and so on with the other values)

    // Select the LCDM memory register index (idx) and bit depending upon the provided Symbol value
    switch ( Symbol )
    {
    case LCD_TMR:
        idx = LCD_TIMER_IDX;
        bit = LCD_TIMER_COM;
        break;
    case LCD_HRT:
        idx = LCD_HEART_IDX;
        bit = LCD_HEART_COM;
        break;
    case LCD_REC:
        idx = LCD_REC_IDX;
        bit = LCD_REC_COM;
        break;
    case LCD_EXCLAMATION:
        idx = LCD_EXCLAMATION_IDX;
        bit = LCD_EXCLAMATION_COM;
        break;
    case LCD_BATT:
        idx = LCD_BATT_IDX;
        bit = LCD_BATT_COM;
        break;
    case LCD_BRACKETS:
        idx = LCD_BRACKETS_IDX;
        bit = LCD_BRACKETS_COM;
        break;
    case LCD_B6:
        idx = LCD_B6_IDX;
        bit = LCD_B6_COM;
        break;
    case LCD_B5:
        idx = LCD_B5_IDX;
        bit = LCD_B5_COM;
        break;
    case LCD_B4:
        idx = LCD_B4_IDX;
        bit = LCD_B4_COM;
        break;
    case LCD_B3:
        idx = LCD_B3_IDX;
        bit = LCD_B3_COM;
        break;
    case LCD_B2:
        idx = LCD_B2_IDX;
        bit = LCD_B2_COM;
        break;
    case LCD_B1:
        idx = LCD_B1_IDX;
        bit = LCD_B1_COM;
        break;
    case LCD_ANT:
        idx = LCD_ANT_IDX;
        bit = LCD_ANT_COM;
        break;
    case LCD_TX:
        idx = LCD_TX_IDX;
        bit = LCD_TX_COM;
        break;
    case LCD_RX:
        idx = LCD_RX_IDX;
        bit = LCD_RX_COM;
        break;
    case LCD_NEG:
        idx = LCD_NEG_IDX;
        bit = LCD_NEG_COM;
        break;
    case LCD_DEG:
        idx = LCD_DEG_IDX;
        bit = LCD_DEG_COM;
        break;
    case LCD_A1DP:
        idx = LCD_A1DP_IDX;
        bit = LCD_A1DP_COM;
        break;
    case LCD_A2DP:
        idx = LCD_A2DP_IDX;
        bit = LCD_A2DP_COM;
        break;
    case LCD_A3DP:
        idx = LCD_A3DP_IDX;
        bit = LCD_A3DP_COM;
        break;
    case LCD_A4DP:
        idx = LCD_A4DP_IDX;
        bit = LCD_A4DP_COM;
        break;
    case LCD_A5DP:
        idx = LCD_A5DP_IDX;
        bit = LCD_A5DP_COM;
        break;
    case LCD_A2COL:
        idx = LCD_A2COL_IDX;
        bit = LCD_A2COL_COM;
        break;
    case LCD_A4COL:
        idx = LCD_A4COL_IDX;
        bit = LCD_A4COL_COM;
        break;
    default:
        break;
    }

    // This switch acts upon the correct icon segment based upon the Operation specified by the user
    switch ( Operation )
    {
    case LCD_UPDATE:
        LCDMEM[ idx - 1 + mem ] |= bit;
        break;
    case LCD_CLEAR:
        LCDMEM[ idx - 1 + mem ] &= ~bit;
        break;
    case LCD_TOGGLE:
        LCDMEM[ idx - 1 + mem ] ^= bit;
        break;
    }

    // The LCD_GET operation is always performed; this is what is returned by the function
    if ( ( LCDMEM[ idx - 1 + mem ] & bit ) >> 0 )
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }

    return ( ret );
}


//*****************************************************************************
// The LCD_C and LCD_E Driver Library modules vary in their implementations. In
// this case, it's not a difference in hardware, but with the fact that some of
// the routines, such as _setMemory(), were improved in the later LCD_E module.
//
// We created a new set of functions here for LCD_C that better match those
// found in the LCD_E implementation. Along with our "myLCD" precursor, we also
// differentiated these functions by adding "Bits" to the end of the function
// names. For example, myLCD_setMemoryBits().
//*****************************************************************************
void myLCD_setMemoryBits( uint8_t LcdMemIndex , uint8_t SegmentMask )           // Set byte-wide LCD Memory with 8-bit SegmentMask
{
    LCDMEM[ LcdMemIndex - 1 ] = SegmentMask;                                    // 'Set' replaces the LCD memory value with the provided mask
}

void myLCD_setBlinkingMemoryBits( uint8_t LcdMemIndex , uint8_t SegmentMask )   // Set byte-wide LCD Memory with 8-bit SegmentMask
{
    LCDBMEM[ LcdMemIndex - 1 ] = SegmentMask;                                   // 'Set' replaces the LCD memory value with the provided mask
}

void myLCD_updateMemoryBits( uint8_t LcdMemIndex , uint8_t SegmentMask )        // Update LCD Memory with 8-bit SegmentMask
{
    LCDMEM[ LcdMemIndex - 1 ] |= SegmentMask;                                   // 'Update' OR's the 8-bit mask with the current LCD memory value
}

void myLCD_updateBlinkingMemoryBits( uint8_t LcdMemIndex , uint8_t SegmentMask ) // Update LCD Memory with 8-bit SegmentMask
{
    LCDBMEM[ LcdMemIndex - 1 ] |= SegmentMask;                                  // 'Update' OR's the 8-bit mask with the current LCD memory value
}

void myLCD_clearMemoryBits( uint8_t LcdMemIndex , uint8_t SegmentMask )         // Clear specified SegmentMask bits of LCD Memory
{
    LCDMEM[ LcdMemIndex - 1 ] &= ~SegmentMask;                                  // 'Clear' AND's the inverse of the provided 8-bit mask
}

void myLCD_clearBlinkingMemoryBits( uint8_t LcdMemIndex , uint8_t SegmentMask ) // Clear specified SegmentMask bits of LCD Memory
{
    LCDBMEM[ LcdMemIndex - 1 ] &= ~SegmentMask;                                 // 'Clear' AND's the inverse of the provided 8-bit mask
}

void myLCD_toggleMemoryBits( uint8_t LcdMemIndex , uint8_t SegmentMask )        // Toggle the bits specified by the 8-bit SegmentMask
{
    LCDMEM[ LcdMemIndex - 1 ] ^= SegmentMask;                                   // 'Toggle' exclusive-OR's the mask bits within the specified LCD memory location
}

void myLCD_toggleBlinkingMemoryBits( uint8_t LcdMemIndex , uint8_t SegmentMask ) // Toggle the bits specified by the 8-bit SegmentMask
{
    LCDBMEM[ LcdMemIndex - 1 ] ^= SegmentMask;                                  // 'Toggle' exclusive-OR's the mask bits within the specified LCD memory location
}

uint8_t myLCD_getMemoryBits( uint8_t LcdMemIndex )                              // Get the byte-wide LCD Memory location
{
    return( LCDMEM[ LcdMemIndex - 1 ] );                                        // 'Get' returns the current value of the specified LCD memory location
}

uint8_t myLCD_getBlinkingMemoryBits( uint8_t LcdMemIndex )                      // Get the byte-wide LCD Memory location
{
    return( LCDBMEM[ LcdMemIndex - 1 ] );                                       // 'Get' returns the current value of the specified LCD memory location
}
