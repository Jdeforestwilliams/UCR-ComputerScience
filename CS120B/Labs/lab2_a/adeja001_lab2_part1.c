/*
 * adeja001_lab2_part1.c - April 12, 2013
 * Name: Ariana DeJaco  E-mail:adeja001@ucr.edu
 * CS Login: adeja001
 * Partner Name: Joshua DeForest-Williams E-mail jdefo002@ucr.edu
 * Lab Section: 022
 * Assignment: Lab#2 Exercise#1 
 * Exercise Description: Count the number of 1s on ports A and B and output that number on port C
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
#define OUTPUT_DDR			DDRC
#define OUTPUT_INPORT		PINC
#define OUTPUT_OUTPORT		PORTC
#define COUNT_A_DDR			DDRA
#define COUNT_A_INPORT		PINA
#define COUNT_A_OUTPORT		PORTA
#define COUNT_B_DDR			DDRB
#define COUNT_B_INPORT		PINB
#define COUNT_B_OUTPORT		PORTB

// Additional macros not defines in sfr_defs.h
//#define SET_PORT_BIT(OUTPORT, BIT)		OUTPORT |= (1 << BIT)
//#define CLEAR_PORT_BIT(OUTPORT, BIT)	OUTPORT &= ~(1 << BIT)

//DDRA: Configures each of port A's physical pins to input (0) or output (1)
//PORTA: Writing to this register writes the port's physical pins (Write only)
//PINA: Reading this register reads the values of the port's physical pins (Read only)
int main(void)
{
	OUTPUT_DDR = 0xFF; //Configures port C's 8 pins as outputs.
	OUTPUT_OUTPORT = 0x00; //Initialize output on port C to 0x00; 
	COUNT_A_DDR = 0x00; // Configure Port A's 8 pins as inputs. 
	//COUNT_A_OUTPORT = 0xFF; // Configure Port A's 8 pins as inputs. 
	COUNT_B_DDR = 0x00; // Configure Port B's 8 pins as inputs.
	//COUNT_B_OUTPORT = 0xFF; // Configure Port B's 8 pins as inputs.  
	
	char loop_counter; 
	char count;
    while(1)
    {
       count = 0; 
        for (loop_counter=0; loop_counter<8; loop_counter++)
		{
			if (GetBit(COUNT_A_INPORT, loop_counter))
			{
				count +=1 ; 
			}				
			
			if(GetBit(COUNT_B_INPORT, loop_counter))
			{
				count +=1; 
			}				
			}
		OUTPUT_OUTPORT = count;
		}
		 
	}
