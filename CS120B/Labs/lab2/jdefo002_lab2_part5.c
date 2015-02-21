/*
 * jdefo002_lab2_part5.c - April 8, 2013
 * Name: Joshua DeForest-Williams E-mail jdefo002@ucr.edu
 * CS Login: jdefo002
 * Partner Name: Ariana DeJaco  E-mail:adeja001@ucr.edu
 * Lab Section: 022
 * Assignment: Lab#1 Exercise#5
 * Exercise Description: (Challenge): A car's passenger-seat weight
 * sensor outputs a 9-bit value (ranging from 0 to 511) and connects
 * to input PD7..PD0PB0 on the microcontroller. If the weight is equal
 * to or above 70 pounds, the airbag should be enabled by setting PB1 to
 * 1. If the weight is above 5 but below 70, the airbag should be
 * disabled and an "Airbag disabled" icon should light by setting PB2 to
 * 1. (Neither B0 nor B1 should be set if the weight is 5 or less,
 * as there is no passenger).
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
#define WEIGHT_DDR		DDRD
#define WEIGHT_INPORT	PIND
#define WEIGHT_OUTPORT  PORTD
#define AIRBAG_DDR	   DDRB
#define AIRBAG_INPORT	PINB
#define AIRBAG_OUTPORT	PORTB

// Additional macros not defines in sfr_defs.h
#define SET_PORT_BIT(OUTPORT, BIT)		OUTPORT |= (1 << BIT)
#define CLEAR_PORT_BIT(OUTPORT, BIT)	OUTPORT &= ~(1 << BIT)

//DDRA: Configures each of port A's physical pins to input (0) or output (1)
//PORTA: Writing to this register writes the port's physical pins (Write only)
//PINA: Reading this register reads the values of the port's physical pins (Read only)
int main(void)
{
   long weight;
   char airbag = 0;
	WEIGHT_DDR = 0x00;
   WEIGHT_OUTPORT = 0xFF;
	AIRBAG_DDR = 0xFE;
   AIRBAG_OUTPORT = 0x01;
   while(1)
   {
      airbag = 0;
      weight = (WEIGHT_INPORT << 1);
      weight = weight | (AIRBAG_INPORT & 0x01);
      if (weight >= 70)
      {
         SET_PORT_BIT(airbag, 1);
      }
      else if (weight < 70 && weight >5)
      {
         CLEAR_PORT_BIT(airbag,1);
         SET_PORT_BIT(airbag, 2);
      }
      else if (weight < 5)
      {
         CLEAR_PORT_BIT(airbag,0);
         CLEAR_PORT_BIT(airbag,1);
      }
      AIRBAG_OUTPORT = airbag;

   }
}