/* adeja001_lab4_partchallenge.c - April 22, 2013
 * Name: Ariana DeJaco E-mail adeja001@ucr.edu
 * CS Login: adeja001
 * Partner Name: Joshua DeForest-Williams E-mail jdefo002@ucr.edu
 * Lab Section: 022
 * Assignment: Lab#4 Exercise#Challenge
 * Exercise Description: Create your own festive lights display with 6 LEDs connected to PC5-PC0
 * lighting in some attractive sequence. Pressing the button on PA0 changes the lights to the next 
 * configuration in the sequence. 
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

unsigned char TckFct_Counter(unsigned char inputData, unsigned char LedValue)
{
	unsigned char TempLedValue = LedValue; 
	
	switch(CurrentState)
	{
		//Transitions
		case InitReset:  // Initial Transition
			CurrentState = WaitForButtonRelease; 
			break;
		case Increment:
		    if(inputData == 0x00)
			{
				CurrentState = WaitForButtonPress;
			}
			else 
			{
				CurrentState = WaitForButtonRelease;
				ActionState = Increment; 
			}
			break; 
		case Decrement:
			if(inputData == 0x00)
			{
				CurrentState = WaitForButtonPress;
			}
			else
			{
				CurrentState = WaitForButtonRelease;
				ActionState = Decrement;
			}
			break;
		case ShiftRight:
			if(inputData == 0x00)
			{
				CurrentState = WaitForButtonPress;
			}
			else
			{
				CurrentState = WaitForButtonRelease;
				ActionState = ShiftRight;
			}
			break;
		case ShiftLeft:
			if(inputData == 0x00)
			{
				CurrentState = WaitForButtonPress;
			}
			else
			{
				CurrentState = WaitForButtonRelease;
				ActionState = ShiftLeft; 
			}
			break;
		case WaitForButtonPress: 
		    if(inputData == 0x00)
			{
				CurrentState = WaitForButtonPress; 
			}
			else
			{
				switch(ActionState)
				{
					case InitReset:
						CurrentState = ShiftLeft;
						break;
					case ShiftLeft:
						CurrentState = ShiftRight;
						break;
					case ShiftRight:
						CurrentState = Increment;
						break;
					case Increment:
						CurrentState = Decrement;
						break; 
					case Decrement:
						CurrentState = ShiftLeft; 
						break;
					default:
						CurrentState = ErrorState;
						break;
				}
			}
		case WaitForButtonRelease:
		    if(inputData == 0x00)
			{
				CurrentState = WaitForButtonPress;
			} 
			break; 
		case ErrorState:
			break; 
		default: 
			CurrentState = ErrorState; 
			break;
	}
	
	switch(CurrentState)
	{
		case InitReset:
			TempLedValue = 0x00;
			break;
		case Decrement:
			TempLedValue = 0x3F; 
			break;
		case Increment:
			TempLedValue = 0x00; 
			break;
		case ShiftLeft:
			TempLedValue = 0x01; 
			break;
		case ShiftRight:
			TempLedValue = 0x20;
			break;
		case WaitForButtonRelease: //If button pressed or button released do the action state
		case WaitForButtonPress:
			switch(ActionState)
			{
				case Increment:
				    if(TempLedValue < 0x3F)
					{
						TempLedValue++;
					}
					else
					{
						TempLedValue = 0x00; 
					}					
					break;
				case Decrement:
					if(TempLedValue > 0x00)
					{
						TempLedValue--;
					}
					else
					{
						TempLedValue = 0x3F; 
					}
					break;
				case InitReset:
					TempLedValue = 0x00;
					break;
				case ShiftLeft:
					if(TempLedValue < 0x20)
					{
						TempLedValue <<= 1;
					}
					else 
					{
						TempLedValue = 0x01; 					
					}					
					break;
				case ShiftRight:
					if(TempLedValue > 0x01)
					{
						TempLedValue >>= 1;
					}		
					else
					{
						TempLedValue = 0x20;
					}			
					break;
				case WaitForButtonPress:
					TempLedValue = 0xFF; // Indicate Error
					break;
				case WaitForButtonRelease:
					TempLedValue = 0xFF; // Indicate Error
					break;
				case ErrorState:
					TempLedValue = 0xFF; // Indicate Error
					break;
				default:
					break;
			}
			break; 	
	}
	return TempLedValue;
}

int main(void)
{
	SENSOR_DDR = 0x00; 
	LED_DDR    = 0xFF; 
	UNUSEDB_DDR= 0x00; 
	UNUSEDD_DDR= 0x00; 
	
	LED_OUTPORT = 0x00; 
	unsigned char ButtonValue = 0; 
	unsigned char CurrentLEDValue = 0; 
	
    while(1)
    {	
		// De-bounce the switch
		while (ButtonValue != (~SENSOR_INPORT & 0x01))
		{
			_delay_ms(50);
			ButtonValue = (~SENSOR_INPORT & 0x01);
		}
		
		CurrentLEDValue = TckFct_Counter(ButtonValue, CurrentLEDValue);
		LED_OUTPORT = CurrentLEDValue;
		
		// Delay for the blinking lights. 
		_delay_ms(250); 
    }
}