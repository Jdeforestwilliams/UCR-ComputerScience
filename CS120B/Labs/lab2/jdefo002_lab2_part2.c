/*
 * jdefo002_lab2_part2.c - April 8, 2013
 * Name: Joshua DeForest-Williams E-mail jdefo002@ucr.edu
 * CS Login: jdefo002
 * Partner Name: Ariana DeJaco  E-mail:adeja001@ucr.edu
 * Lab Section: 022
 * Assignment: Lab#1 Exercise#2
 * Exercise Description: A car has a fuel-level sensor that sets PA3..PA0 to a value between 0 (empty) and 15 (full).
 * A series of LEDs connected to PC5..PC0 should light to graphically indicate the fuel level. If the fuel level is 1 or 2,
 * PC5 lights. If the level is 3 or 4, PC5 and PC4 light. Level 5-6 lights PC5..PC3. 7-9 lights PC5..PC2. 10-12
 * lights PC5..PC1. 13-15 lights PC5..PC0. Also, PC6 connects to a "Low fuel" icon, which should light if the level is 4 or less.
 * (The example below shows the display for a fuel level of 3).
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
#define LED_DDR				DDRC
#define LED_INPORT			PINC
#define LED_OUTPORT			PORTC
#define SENSOR_DDR			DDRA
#define SENSOR_INPORT		PINA
#define SENSOR_OUTPORT		PORTA

// Additional macros not defines in sfr_defs.h
#define SET_PORT_BIT(OUTPORT, BIT)		OUTPORT |= (1 << BIT)
#define CLEAR_PORT_BIT(OUTPORT, BIT)	OUTPORT &= ~(1 << BIT)

//DDRA: Configures each of port A's physical pins to input (0) or output(1)
//PORTA: Writing to this register writes the port's physical pins
// (Write only)
//PINA: Reading this register reads the values of the port's physical pins
// (Read only)
int main(void)
{
   SENSOR_DDR = 0x00; 
   SENSOR_OUTPORT = 0xFF; // Configure port A's 8 pins as inputs
	LED_DDR = 0xFF; 
   LED_OUTPORT = 0x00; // Configure port C's 8 pins as outputs,
   const unsigned char Low_level = 0;
   const unsigned char Sec_low_level = 2;
   const unsigned char Mid_low_level = 4;
   const unsigned char Mid_Hi_level = 6;
   const unsigned char Sec_Hi_level = 9;
   const unsigned char High_level =12;

    while(1)
    {
       char led = 0;
       if (SENSOR_INPORT > High_level)
         {
            SET_PORT_BIT  (led,5);
         }            
      if (SENSOR_INPORT > Sec_Hi_level)
         {
            SET_PORT_BIT (led,4);
         }         
      if (SENSOR_INPORT > Mid_Hi_level)
         {
            SET_PORT_BIT(led,3); 
         }         
      if (SENSOR_INPORT > Mid_low_level)
         {
            SET_PORT_BIT(led,2);
         }            
      if (SENSOR_INPORT > Sec_low_level)      
         {
            SET_PORT_BIT(led,1);
         }            
      if (SENSOR_INPORT > Low_level )
         {
            SET_PORT_BIT(led,0);
         }         
      if (SENSOR_INPORT <= Mid_low_level)
         {
            SET_PORT_BIT(led,6);
         }         
       LED_OUTPORT = led;
      }
   }
    
         
                
  
      
     