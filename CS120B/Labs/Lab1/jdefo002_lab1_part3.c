/*
 * jdefo002_lab1_part3.c - April 8, 2013
 * Name: Joshua DeForest-Williams jdefo002@ucr.edu
 * CS Login: jdefo002
 * Partner Name: Ariana DeJaco  E-mail:adeja001@ucr.edu 
 * Lab Section: 022
 * Assignment: Lab#1 Exercise# Part3
 * Exercise Description: Extension of the second part of this lab that writes the available spaces number to only PC3..PC0, 
 *						 and to set PC7 to 1 if the lot is full.  
*/

#include <avr/io.h>
#include <avr/sfr_defs.h>

// DDR = Data Direction Register. Shows which bits are outputs and which are inputs. Inputs = 0. Outputs = 1. 

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
	LED_DDR = 0x8F;
	
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
				
		if(freespaces == 0)
		{
			LED_OUTPORT = 0x80;
		}		
		else
		{
			LED_OUTPORT = freespaces;
		}		
	}
}
