/*
 * jdefo002_lab1_part2.c - April 8, 2013
 * Name: Joshua DeForest-Williams E-mail jdefo002@ucr.edu
 * CS Login: jdefo002
 * Partner Name: Ariana DeJaco  E-mail:adeja001@ucr.edu
 * Lab Section: 022
 * Assignment: Lab#1 Exercise# Part2
 * Exercise Description: Program outputs in binary on port C the number of available spaces.  
*/


#include <avr/io.h>
#include <avr/sfr_defs.h>

// Current Port Definitions
#define LED_DDR			DDRC
#define LED_INPORT		PINC
#define LED_OUTPORT		PORTC
#define SENSOR_DDR		DDRA
#define SENSOR_INPORT	PINA
#define SENSOR_OUTPORT	PORTA

// Additional macros not defines in sfr_defs.h
#define SET_PORT_BIT(OUTPORT, BIT)		OUTPORT |= (1 << BIT)
#define CLEAR_PORT_BIT(OUTPORT, BIT)	OUTPORT &= ~(1 << BIT)

int main(void)
{
	SENSOR_DDR = 0x00;
	LED_DDR = 0xFF; 
	
	char freespaces; 
	
    while(1)
    {
		freespaces = 0;
		for(char i = 0; i < 4; i++)
		{
			if(!(bit_is_set(SENSOR_INPORT, i)))
			{
				freespaces++;
			}			
		}
				
		LED_OUTPORT = freespaces;
    }
}
