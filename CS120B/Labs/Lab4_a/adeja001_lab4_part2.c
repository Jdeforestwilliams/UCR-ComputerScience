 /* adeja001_lab4_part2.c - April 22, 2013
 * Name: Ariana DeJaco Email adeja001@ucr.edu
 * CS Login: adeja001
 * Partner Name: Joshua DeForest-Williams E-mail jdefo002@ucr.edu
 * Lab Section: 022
 * Assignment: Lab#4 Exercise#2
 * Exercise Description: Buttons are connected to PA0 and PA1. Output for PORTC is initially 0. 
 * Pressing PA0 increments PORTC. Pressing PA1 decrements. If both are pressed, PORTC is reset. 
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

enum Counter_States { InitReset, Increment, Decrement, WaitForButtonPress, WaitForButtonRelease, ErrorState } CounterState;

unsigned char TckFct_Counter(unsigned char inputData, unsigned char LedValue)
{
	// Variable we are returning
	unsigned char tempLedValue = LedValue; 
	
	switch(CounterState)
	{
		//Transitions
		case InitReset:  // Initial Transition
			CounterState = WaitForButtonRelease; 
			break;
		case Increment:
		    CounterState = WaitForButtonRelease;
			break; 
		case Decrement:
			CounterState = WaitForButtonRelease;
			break;
		case WaitForButtonPress: 
		    if(inputData == 0x00)
			{
				CounterState = WaitForButtonPress; 
			}
			else if(inputData == 0x01)
			{
				if(tempLedValue < 9)
				{
					CounterState = Increment;
				}			    
				// Will stay in wait if not < 9
			}
			else if(inputData == 0x02)
			{
				if(tempLedValue > 0)
				{
					CounterState = Decrement;
				}
				// Will stay in wait if not > 0
			}
			else if(inputData == 0x03)
			{
				CounterState = InitReset;
			}
			else
			{
				CounterState = ErrorState; 
			}
			break; 
		case WaitForButtonRelease:
		    if(inputData == 0x00)
			{
				CounterState = WaitForButtonPress;
			} 
			break; 
		case ErrorState:
			break; 
		default: 
			CounterState = ErrorState; 
			break;
	}
	
	switch(CounterState)
	{ // Actions
		case Increment:
			tempLedValue++; 
			break;
		case Decrement:
			tempLedValue--;
			break; 
		case InitReset:
			tempLedValue = 0x00; 
			break;
		case WaitForButtonPress:
			break;
		case WaitForButtonRelease:
			break;
		case ErrorState:
			tempLedValue = 0xFF; 
			break; 
		default:
			break;
	}
	return tempLedValue;
}

int main(void)
{
	SENSOR_DDR = 0x00; 
	LED_DDR    = 0xFF; 
	UNUSEDB_DDR= 0x00; 
	UNUSEDD_DDR= 0x00; 
	
	// Initialize LEDs to off
	LED_OUTPORT = 0x00; 
	unsigned char ButtonValue = 0; 
	unsigned char CurrentLEDValue = 0; 
	
    while(1)
    {	
		// Code to debounce the switch. 
		while (ButtonValue != (~SENSOR_INPORT & 0x03))
		{
			_delay_ms(50); 
			ButtonValue = (~SENSOR_INPORT & 0x03);
		}
	
		CurrentLEDValue = TckFct_Counter(ButtonValue, CurrentLEDValue);
		LED_OUTPORT = CurrentLEDValue; 
    }
}