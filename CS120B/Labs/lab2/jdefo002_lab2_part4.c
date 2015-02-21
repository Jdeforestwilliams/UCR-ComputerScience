/*
 * jdefo002_lab2_part4.c - April 8, 2013
 * Name: Joshua DeForest-Williams E-mail jdefo002@ucr.edu
 * CS Login: jdefo002
 * Partner Name: Ariana DeJaco  E-mail:adeja001@ucr.edu
 * Lab Section: 022
 * Assignment: Lab#1 Exercise#4
 * Exercise Description: (Challenge): Read an 8-bit value on PA7..PA0
 * and write that value on PB3..PB0PC7..PC4. That is to say,
 * take the upper nibble of PINA and map it to the lower nibble of PORTB,
 * likewise take the lower nibble of PINA and map it to the upper
 * nibble of PORTC (PA7 -> PB3, PA6 -> PB2, … PA1 -> PC5, PA0 -> PC4).
 */

#include <avr/io.h>
#include <avr/sfr_defs.h>

// Bit-access function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

// Current Port Definitions
#define HIGH_NIB_DDR			DDRC
#define HIGH_NIB_INPORT		PINC
#define HIGH_NIB_OUTPORT	PORTC
#define FULL_NIB_DDR			DDRA
#define FULL_NIB_INPORT		PINA
#define FULL_NIB_OUTPORT	PORTA
#define LOW_NIB_DDR			DDRB
#define LOW_NIB_INPORT		PINB
#define LOW_NIB_OUTPORT		PORTB

// Additional macros not defines in sfr_defs.h
//#define SET_PORT_BIT(OUTPORT, BIT)		OUTPORT |= (1 << BIT)
//#define CLEAR_PORT_BIT(OUTPORT, BIT)	OUTPORT &= ~(1 << BIT)

//DDRA: Configures each of port A's physical pins to input (0) or output (1)
//PORTA: Writing to this register writes the port's physical pins (Write only)
//PINA: Reading this register reads the values of the port's physical pins (Read only)
int main(void)
{
	HIGH_NIB_DDR = 0xFF; //Configures port C's 8 pins as outputs.
	HIGH_NIB_OUTPORT = 0x00; //Initialize output on port C to 0x00;
	FULL_NIB_DDR = 0x00; // Configure Port A's 8 pins as inputs.
   FULL_NIB_OUTPORT = 0xFF; // Configure Port A's 8 pins as inputs.
	LOW_NIB_DDR = 0x00; // Configure Port B's 8 pins as inputs.
	LOW_NIB_OUTPORT = 0xFF; // Configure Port B's 8 pins as inputs.
   while(1)
   {
      //PORTC (PA7 -> PB3, PA6 -> PB2, … PA1 -> PC5, PA0 -> PC4).
    char temp_low_nib = (FULL_NIB_INPORT >> 4);
    LOW_NIB_OUTPORT = temp_low_nib;
    char temp_high_nib = (FULL_NIB_INPORT & 0x0f) << 4;
    HIGH_NIB_OUTPORT = temp_high_nib;
   }
}