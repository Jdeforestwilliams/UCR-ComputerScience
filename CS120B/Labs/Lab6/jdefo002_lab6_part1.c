/* jdefo002_lab6_part1.c - April 29, 2013
 * Name: Joshua DeForest-Williams E-mail jdefo002@ucr.edu
 * CS Login: jdefo002
 * Partner Name: Ariana DeJaco Email adejaoo1@ucr.edu
 * Lab Section: 022
 * Assignment: Lab#6 Exercise#1
 * Exercise Description: Create a synchSM to blink three LEDs 
 * connected to PB0, PB1, and PB2 in sequence, 1 second each. 
 * Implement that synchSM in C using the method defined in class. 
 * In addition to demoing your program, you will need to show that 
 * your code adheres entirely to the method with no variations. 
 */

#include <avr/io.h>
#include <avr/interrupt.h>

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
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

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

enum BL_States { Initial, BL_LedOff, BL_LedOneOn, BL_LedTwoOn, BL_LedThreeOn } BL_State;
	
void TickFct_Blink() 
{
	switch ( BL_State ) 
	{ //Transitions
		case Initial:
			BL_State = BL_LedOff; //Initial state
			break;
		case BL_LedOff:
			BL_State = BL_LedOneOn;
			break;
		case BL_LedOneOn:
			BL_State = BL_LedTwoOn;
			break;
		case BL_LedTwoOn:
			BL_State = BL_LedThreeOn;
			break;
		case BL_LedThreeOn:
			BL_State = BL_LedOff; 	
			break;
		default:
			BL_State = -1;
		break;
	}
	
	switch (BL_State ) 
	{ //State actions
		case BL_LedOff:
			LED_OUTPORT = 0x00;
			break;
		case BL_LedOneOn:
			LED_OUTPORT = 0x01; 
			break;
		case BL_LedTwoOn:
			LED_OUTPORT = 0x02;
			break;
		case BL_LedThreeOn:
			LED_OUTPORT = 0x04; 
			break;
		default:
			break;
	}
}

void main()
{
	LED_DDR = 0xFF; // Set port B to output
	LED_OUTPORT = 0x00; // Init port B to 0s
	
	TimerSet(1000);
	TimerOn();
	
	BL_State = Initial; // Indicates initial tick function call
	
	while(1) 
	{
		TickFct_Blink(); // Execute one tick of the BL synchSM
		while (!TimerFlag){} // Wait for BL’s period
		TimerFlag = 0; 
	}
}
