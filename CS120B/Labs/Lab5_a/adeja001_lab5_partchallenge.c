/* adeja001_lab4_part1.c - April 22, 2013
 * Name: Ariana DeJaco Email adejaoo1@ucr.edu
 * CS Login: adeja001
 * Partner Name: Joshua DeForest-Williams E-mail jdefo002@ucr.edu
 * Lab Section: 022
 * Assignment: Lab#5 Exercise#challenge
 * Exercise Description: Create a more complex game -- make it fun! 
 * However, still use basic (not synchronous) state machines -- so no time-interval behavior in your game. 
 */

// Used for debouncing the button (How many Hz) 
#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>
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


enum Counter_States { InitReset, LEDLight, WaitForButtonPress, WaitForButtonRelease } CounterState;

unsigned char Write7SegNumber(unsigned char x)
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
		default:
			segvalue = 0x73;
			break;
	}
	
	return segvalue;
}

unsigned char Write7SegLetter(unsigned char randNum, unsigned char guess)
{
	unsigned char segvalue = 0;
	unsigned char ranvalue = randNum;
	
	if(randNum < guess)
	{
		segvalue = 0x6D;
	}
	else if(randNum > guess)
	{
		segvalue = 0x23;
	}
	else if(randNum == guess)
	{
		segvalue = Write7SegNumber(ranvalue);
	}
	else
	{
		segvalue = 0x00;
	}
	
	return segvalue;
}

unsigned char TckFct_Counter(unsigned char inputData, unsigned char randNum, unsigned char sevSegVal)
{
	// Variable we are returning
	unsigned char tempLedValue = sevSegVal;
	
	switch(CounterState)
	{
		//Transitions
		case InitReset:  // Initial Transition
			CounterState = WaitForButtonRelease;
			break;
		case LEDLight:
			CounterState = WaitForButtonRelease;
			break;
		case WaitForButtonPress:
			if(inputData == 0x00)
			{
				CounterState = WaitForButtonPress;
			}
			else 
			{
				CounterState = LEDLight; 
			}
			break;
		case WaitForButtonRelease:
			if(inputData == 0x00)
			{
				CounterState = WaitForButtonPress;
			}
			break;
		default:
			CounterState = InitReset;//ErrorState;
			break;
	}
	
	switch(CounterState)
	{ // Actions
		case LEDLight:
			tempLedValue = Write7SegLetter(inputData, randNum);
			break;
		case InitReset:
			tempLedValue = 0x00;
			break;
		case WaitForButtonPress:
			break;
		case WaitForButtonRelease:
			break;
		default:
			break;
	}
	return tempLedValue;
}

int rand(void);

int main(void)
{
	SENSOR_DDR = 0x00; 
	LED_DDR    = 0xFF; 
	UNUSEDB_DDR= 0x00; 
	UNUSEDD_DDR= 0x00; 
	
	// Initialize LEDs to off
	LED_OUTPORT = 0x00; 
	unsigned char ButtonValue = 0; 
	unsigned char SevenSegValue = 0;
	
	unsigned char RandNumber = 4;
	
    while(1)
    {	
		// Code to debounce the switch. 
		while (ButtonValue != (~SENSOR_INPORT & 0x0F))
		{
			_delay_ms(50); 
			ButtonValue = (~SENSOR_INPORT & 0x0F);
		}
		
		SevenSegValue = TckFct_Counter(ButtonValue, RandNumber, SevenSegValue);
		LED_OUTPORT = SevenSegValue; 
    }
}