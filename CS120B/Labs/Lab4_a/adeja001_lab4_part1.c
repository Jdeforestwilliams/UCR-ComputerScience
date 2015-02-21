 /* adeja001_lab4_part1.c - April 22, 2013
 * Name: Ariana DeJaco E-mail adeja001@ucr.edu
 * CS Login: adeja001
 * Partner Name: Joshua DeForest-Williams E-mail jdefo002@ucr.edu
 * Lab Section: 022
 * Assignment: Lab#4 Exercise#1
 * Exercise Description: A car has a fuel-level sensor that sets PA3..PA0 to a value between 0 (empty) and 15 (full).
 * A series of LEDs connected to PC5..PC0 should light to graphically indicate the fuel level. If the fuel level is 1 or 2,
 * PC5 lights. If the level is 3 or 4, PC5 and PC4 light. Level 5-6 lights PC5..PC3. 7-9 lights PC5..PC2. 10-12
 * lights PC5..PC1. 13-15 lights PC5..PC0. Also, PC6 connects to a "Low fuel" icon, which should light if the level is 4 or less.
 * (The example below shows the display for a fuel level of 3).
 */


 #include <avr/io.h>
 #include <avr/sfr_defs.h>

 // Bit-access function
 unsigned char GetBit(unsigned char x, unsigned char k) 
 {
	 return ((x & (0x01 << k)) != 0);
 }
 
 // Current Port Definitions
 #define LED_DDR				DDRC
 #define LED_INPORT			PINC
 #define LED_OUTPORT			PORTC
 #define SENSOR_DDR			DDRA
 #define SENSOR_INPORT		PINA
 #define SENSOR_OUTPORT		PORTA
 #define UNUSEDB_DDR        DDRB
 #define UNUSEDB_PIN        PINB
 #define UNUSEDB_PORT       PORTB
 #define UNUSEDD_DDR        DDRD
 #define UNUSEDD_PIN        PIND
 #define UNUSEDD_PORT       PORTD
 
 // All "fuel levels" defined as macros, makes easy to change
 #define LEVEL1 2
 #define LEVEL2 4
 #define LEVEL3 6
 #define LEVEL4 9
 #define LEVEL5 12

 // Additional macros not defines in sfr_defs.h
 #define SET_PORT_BIT(OUTPORT, BIT)		OUTPORT |= (1 << BIT)
 #define CLEAR_PORT_BIT(OUTPORT, BIT)	OUTPORT &= ~(1 << BIT)

// Function to set all the LED lights according to the Fuel Level. 
unsigned char TickFct_gas(char SensorValue)
{
	unsigned char ledValue;
	
    if (SensorValue > LEVEL5)
	{
	    ledValue = 0x3F;
	}	
    else if (SensorValue > LEVEL4)
	{
	    ledValue = 0x3E;
	}	
    else if (SensorValue > LEVEL3)
	{
	    ledValue = 0x3C;
	}	
    else if (SensorValue > LEVEL2)
	{
	    ledValue = 0x38;
	}	
    else if (SensorValue > LEVEL1)
	{
	    ledValue = 0x30;
	}	
	else if (SensorValue > 0)  
	{
	    ledValue = 0x20;
	}	
    else
	{
        ledValue = 0;
	}		
	
	if (SensorValue <= LEVEL2)
	{
	   ledValue |= 0x40;
	}	  
	return ledValue;
}

//DDRA: Configures each of port A's physical pins to input (0) or output(1)
//PORTA: Writing to this register writes the port's physical pins
// (Write only)
//PINA: Reading this register reads the values of the port's physical pins
// (Read only)
int main(void)
{
   SENSOR_DDR = 0x00;   // Configure port A's 8 pins as inputs
   LED_DDR = 0xFF;      // Configure port C's 8 pins as outputs,
   UNUSEDB_DDR = 0X00;
   UNUSEDD_DDR = 0X00;
   
	unsigned char SensorValue = 0;
	unsigned char SavedSensorValue = 0;
   
    while(1)
    {
	   // We are working with inverted logic so we need to use the compliment so 
	   // we use the tilda.. Must also mask out bits we are not using
	   // (in this case A4-A7) 
	   SensorValue = (~SENSOR_INPORT & 0x0F);
	   
	   // Do not need to use the tilda (compliment) when putting into the function 
	   // because we need it to output a 1 in order for LED to light up. 
       LED_OUTPORT = TickFct_gas(SensorValue);
    }
}






