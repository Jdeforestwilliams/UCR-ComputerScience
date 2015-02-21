/* jdefo002_lab4_part1.c - April 22, 2013
 * Name: Joshua DeForest-Williams E-mail jdefo002@ucr.edu
 * CS Login: jdefo002
 * Partner Name: Ariana DeJaco E-mail adeja001@ucr.edu
 * Lab Section: 022
 * Assignment: Lab#5 Exercise#1
 * Exercise Description: Complete the following program by defining
 * the function "void Write7Seg(unsigned char x)" that sets the 
 * 7-segment display to display x for values of 0 to 9. So if x is 0, 
 * illuminate segments A, B, C, D, E, and F (but not G). If x is 1, 
 * illuminate segments B and C. If x > 9, illuminate nothing.  
 * Carefully examine the above photo, the ATmega32 pinout, and the 
 * seven-segment pinout, to properly define the function.
 */

// Use for debouncing the switch (How many Hz) 
#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>

// Bit-access function
unsigned char GetBit(unsigned char x, unsigned char k)
{
	return ((x & (0x01 << k)) != 0);
}

// Bit-set function 
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) 
{
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

// Current Port Definitions
#define LED_DDR				DDRC
#define LED_INPORT			PINC
#define LED_OUTPORT			PORTC
#define SENSOR_DDR			DDRA
#define SENSOR_INPORT		PINA
#define SENSOR_OUTPORT		PORTA
#define UNUSEDB_DDR         DDRB
#define UNUSEDB_PIN         PINB
#define UNUSEDB_PORT        PORTB
#define UNUSEDD_DDR         DDRD
#define UNUSEDD_PIN         PIND
#define UNUSEDD_PORT        PORTD

 // Additional macros not defines in sfr_defs.h
 #define SET_PORT_BIT(OUTPORT, BIT)		OUTPORT |= (1 << BIT)
 #define CLEAR_PORT_BIT(OUTPORT, BIT)	OUTPORT &= ~(1 << BIT)

//DDRA: Configures each of port A's physical pins to input (0) or output(1)
//PORTA: Writing to this register writes the port's physical pins
// (Write only)
//PINA: Reading this register reads the values of the port's physical pins
// (Read only)

// Creating a type "statetpe" and making 2 variables of this type and initializing them to InitReset
typedef enum { InitReset, Increment, Decrement, WaitForButtonPress, WaitForButtonRelease, ShiftLeft, ShiftRight, ErrorState } statetype;
statetype CurrentState  = InitReset;
statetype ActionState = InitReset; 
#include <avr/io.h>


unsigned char Write7Seg(unsigned char x) 
{
	unsigned char segvalue = 0; 
	switch(x)
	{
		case 0:
			segvalue = 0x3F;
			break;
		case 1:
			segvalue = 0x0C;
			break;
		case 2:
			segvalue = 0x5B;
			break;
		case 3:
			segvalue = 0x5E;
			break;
		case 4:
			segvalue = 0x6C;
			break;
		case 5:
			segvalue = 0x76;
			break;
		case 6:
			segvalue = 0x77;
			break;
		case 7:
			segvalue = 0x1C;
			break;
		case 8:
			segvalue = 0x7F;
			break; 
		case 9:
			segvalue = 0x7C;
			break;
		deault:
			segvalue = 0x73;
			break;
	}
	
	return segvalue;
}

int rand(void);

int main(void)
{
	unsigned char cnt=0;
	DDRA = 0x00; PORTA = 0xFF; // Config port A as inputs, init 1s
	DDRC = 0xFF; PORTC = 0x00; // Config port C as outputs, init 0s
	while(1) {
		if (GetBit(PINA, 0)==0) { // Button pressed
		cnt = rand() % 10; // cnt is rand num from 0-9
		PORTC = Write7Seg(cnt);
	}
}
}
