/* adeja001_lab6_part3.c - April 29, 2013
 * Name: Ariana DeJaco Email adejaoo1@ucr.edu
 * CS Login: adeja001
 * Partner Name: Joshua DeForest-Williams E-mail jdefo002@ucr.edu
 * Lab Section: 022
 * Assignment: Lab#6 Exercise#3/challenge
 * Exercise Description: (Challenge) Create a simple game that
 * requires pressing a button on PA0 while the middle of three 
 * LEDs on PB0, PB1, and PB2 is lit. The LEDs light for 300 ms 
 * each in sequence. When the button is pressed, the currently 
 * lit LED stays lit. Pressing the button again restarts the game.
 */

// Interrupt.h is needed otherwise it will NOT work!!!!

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>

// Bit-access function
unsigned char GetBit(unsigned char x, unsigned char k)
{
	return ((x & (0x01 << k)) != 0);
}

// Current Port Definitions
#define LED_DDR				DDRB
#define LED_INPORT			PINB
#define LED_OUTPORT			PORTB
#define SENSOR_DDR			DDRA
#define SENSOR_INPORT		PINA
#define SENSOR_OUTPORT		PORTA
#define UNUSEDC_DDR         DDRC
#define UNUSEDC_PIN         PINC
#define UNUSEDC_PORT        PORTC
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

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
volatile unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
volatile unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

void TimerOn()
{
	// AVR timer/counter controller register TCCR0
	TCCR0 = 0x0B;	// bit3bit6=10: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT0 register will count at 125,000 ticks/s

	// AVR output compare register OCR0.
	OCR0 = 125;	// Timer interrupt will be generated when TCNT0==OCR0
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT0 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK = 0x02; // bit1: OCIE0 -- enables compare match interrupt

	//Initialize avr counter
	TCNT0=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff()
{
	TCCR0 = 0x00; // bit2bit1bit0=000: timer off
}

void TimerISR()
{
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER0_COMP_vect)
{
	// CPU automatically calls when TCNT0 == OCR0 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0)
	{ // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M)
{
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

enum Counter_States { Init, ShiftLightAndCheck, WinState } CounterState;

unsigned char TckFct_Counter(unsigned char inputData, unsigned char LedValue)
{
	// Variable we are returning
	unsigned char tempLedValue = LedValue; 
	
	switch(CounterState)
	{
		//Transitions
		case Init:  // Initial Transition
			CounterState = ShiftLightAndCheck;
			break;
		case ShiftLightAndCheck:  
			if(LedValue > 0x04)
			{
				CounterState = Init; 
			}
			else if((LedValue == 0x02) && (inputData == 0x01))
			{
				CounterState = WinState;
			}
			else
			{
				CounterState = ShiftLightAndCheck;
			}
			break;
		case WinState:
		    if(inputData == 0x01)
			{
				CounterState = Init;
			}
			else
			{
				CounterState = WinState;
			}
			break; 
		default:  
			break;
	}
	
	switch(CounterState)
	{ // Actions
		case Init:
			tempLedValue = 0x01;	 
			break;
		case ShiftLightAndCheck:
			tempLedValue <<= 1; 
			break; 
		case WinState:
			tempLedValue = 0x02; 
			break; 
		default:
			break;
	}
	return tempLedValue;
}

unsigned char Write7Seg(unsigned char x)
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
		deault:
			segvalue = 0x73;
			break;
	}
	
	return segvalue;
}

int main(void)
{
	SENSOR_DDR = 0x00; 
	LED_DDR    = 0xFF; 
	UNUSEDC_DDR= 0x00; 
	UNUSEDD_DDR= 0x00; 
	
	// Initialize LEDs to off
	LED_OUTPORT = 0x00; 
	unsigned char ButtonValue = 0; 
	unsigned char CanAcceptButtonPressed = 0;
	unsigned char CurrentLEDValue = 0x01;
	unsigned char SevenSegValue = 0;
	
	// The Timer is set to 500 ms because In the increment/decrement state it has
	// to go back to the wait for button press state. Therefore, there are two
	// state transitions, each take up 500ms making a total of 1 second.
	TimerSet(300);
	TimerOn();
	CounterState = Init;
	
	CanAcceptButtonPressed = 1;
    while(1)
    {
		// Wait for 1 second before advancing the state machine. While waiting see if
		// any buttons have been pressed. Save the last button pressed values
		//ButtonValue = 0;    // Assume no buttons have been pressed
		TimerFlag = 0;      // Reset the timer flag. It will be set by the timer0 interrupt.

		// Wait until the timer0 interrupt executes (Once every second)
		ButtonValue = 0;
		while (!TimerFlag)
		{
			 // If some buttons have been pressed then save what has been pressed.
			 if ((~SENSOR_INPORT & 0x03) == 0)
			 {
				 if (CanAcceptButtonPressed == 1)
					ButtonValue = 0;
				 else
				    CanAcceptButtonPressed = 1;
			 }
			 else
			 {
				 if (CanAcceptButtonPressed == 1)
				 {
				    ButtonValue = (~SENSOR_INPORT & 0x03);
					CanAcceptButtonPressed = 0;
				 }		 					
			 }
		}
		if ((CounterState == WinState))
		   CanAcceptButtonPressed = 1;
		// Now that  1 second is up we can advance the state machine
		CurrentLEDValue = TckFct_Counter(ButtonValue, CurrentLEDValue);
		// Write the reset to the seven segment display
		//SevenSegValue = Write7Seg(CurrentLEDValue);
		LED_OUTPORT = CurrentLEDValue; 
    }
}