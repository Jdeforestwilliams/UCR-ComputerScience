/*
 * adeja001_lab1_part1.c - April 8, 2013
 * Name: Ariana DeJaco  E-mail:adeja001@ucr.edu
 * CS Login: adeja001
 * Partner Name: Joshua DeForest-Williams jdefo002@ucr.edu
 * Lab Section: 022
 * Assignment: Lab#1 Exercise# Part 1
 * Exercise Description: Program that illuminates an LED connected to PB0 if the garage door is open at night. 
*/


#include <avr/io.h>
#include <avr/sfr_defs.h>

#define IS_GARAGE_DOOR_SET  (bit_is_set(PINA, PINA0))
#define IS_LIGHT_SENSOR_SET (bit_is_set(PINA, PINA1))
#define SET_LED          PORTB |= (1 << PINB0) 
#define CLEAR_LED        PORTB &= ~(1 << PINB0)

int main(void)
{
	DDRA = 0x00;
	DDRB = 0x01;
	PORTB = 0x00;
	
    while(1)
    {
		if(!(IS_LIGHT_SENSOR_SET) && IS_GARAGE_DOOR_SET)
		{
		  SET_LED;
		}		
		else
		{
		  CLEAR_LED;
		}		  
    }
}