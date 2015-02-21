/*	Partner(s) Name & E-mail:Marcel Tawamba & mtawa002@ucr.edu
 *	Partner(s) Name & E-mail:Joshua DeForest-Williams & jdefo002@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab # 9  Exercise # 1
 *	Exercise Description: Use two buttons (connected to PB0 and PB1) to rotate 
 *  the Stepper motor clockwise or counter-clockwise. Design a state machine that 
 *  transitions between the eight phases: A -> AB -> B -> BC -> C -> CD -> D -> DA -> A ...
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "keypad.h"

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void TimerOn() {
	TCCR1B 	= 0x0B;
	OCR1A 	= 125;
	TIMSK1 	= 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff() {
	TCCR1B 	= 0x00;
}

void TimerISR() {
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect)
{
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

enum SM_States{INIT, wait_input, forward, backward} sm_state;
char position = 0; 
char phases[] = {0x01, 0x03,0x02, 0x06, 0x04, 0x0C, 0x08, 0x09}; //A, AB, B, BC, C, CD, D, DA
unsigned char direction = 0;
void TickFct_part1(){
	direction = (~PINB) & 0x03; 
	switch(sm_state){
		case INIT:
			sm_state = wait_input;
			break;
		case wait_input:
		case forward:
		case backward:
			if (direction == 0x00 || direction == 0x03){
				sm_state = wait_input;
			}
			else if (direction == 0x01)
			{
				sm_state = forward;
			}
			else if (direction == 0x02){
				sm_state = backward;
			}			
			break;			
		default :
			sm_state = INIT;
			break;
	}
	switch(sm_state){
		case wait_input:
			PORTA = phases[position]; 
			break;
		case forward:
			if (position > 7)
			{
				position = 0; 
			}
			PORTA = phases[position];
			position++; 
			break;
		case backward:
			if (position < 1)
			{
				position = 7; 
			}
			PORTA = phases[position];
			position--; 
			break;
		default: 
			break;
	}
}

int main(void)
{
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as inputs
	DDRA = 0xFF; PORTA = 0x00; // Configure port A's 8 pins as inputs
	TimerSet(3);
	TimerOn();
	sm_state = INIT;
		while(1)
	{	
		TickFct_part1();
		while(!TimerFlag);
		TimerFlag = 0;
	}
}