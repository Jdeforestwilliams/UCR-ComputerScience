/*	Partner(s) Name & E-mail: Marcel Tawamba & mtawa002@ucr.edu
 *	Partner(s) Name & E-mail: Joshua DeForest-Williams & jdefo002@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab # 9  Exercise # 3
 *	Exercise Description: Use six buttons to rotate the motor clockwise or 
 *	counter-clockwise 90, 180, or 360 degrees
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "keypad.h"
#include <stdlib.h>

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

enum SM_States{INIT, wait_input, forward/*, backward*/} sm_state;
char position = 0;
int numPhases;
int counter = 0; 
char phases[] = {0x01, 0x03,0x02, 0x06, 0x04, 0x0C, 0x08, 0x09}; //A, AB, B, BC, C, CD, D, DA
int num_degrees = 180;
unsigned char exp1[4];// = { '3', '6', '0', '#' };
unsigned char input_counter = 0; 
unsigned char direction = 0;
void TickFct_part1(){
	//direction = GetKeypadKey(); 
	switch(sm_state){
		case INIT:
			sm_state = wait_input;
			break;
		case wait_input:
			if (direction == '#' ){
				sm_state = forward; 
				num_degrees = atoi(exp1); 
				input_counter = 0; 
				numPhases= (num_degrees / 5.625 /*degrees*/) * 64 /*phases*/;
				//PORTC = num_degrees; 
			}
			else if (direction == '\0'){
				sm_state = wait_input;
				PORTC = direction; //num_degrees;
			}
			else {
				exp1[input_counter] = direction; 
				input_counter++;
				//PORTC = num_degrees; 
				sm_state = wait_input; 
			}
			break;
		case forward:
			if (counter <= numPhases){
				sm_state = forward;
				PORTC = 0x05;
			}
			else {
				sm_state = wait_input;
				counter = 0;
				PORTC= 0x0A;
			}
			break;
		/*case backward:
			if (counter <= numPhases){
				sm_state = backward;
			}
			else {
				sm_state = wait_input;
				counter = 0;
			}
			break;*/		
		default :
			sm_state = INIT;
			break;
	}
	switch(sm_state){
		case wait_input:
			PORTA = phases[position]; 
			break;
		case forward:
		//case forward_half:
		//case forward_full:
			if (position > 7)
			{
				position = 0; 
			}
			PORTA = phases[position];
			//PORTC = 0xFF; 
			position++; 
			counter++;
			break;
		/*case forward_half:
			if (position > 7)
			{
				position = 0;
			}
			PORTA = phases[position];
			position++;
			counter++;
			break;
		case forward_full:
			if (position > 7)
			{
				position = 0;
			}
			PORTA = phases[position];
			position++;
			counter++;
			break;	*/
		/*case backward_quarter:
			if (position < 1)
			{
				position = 7; 
			}
			PORTA = phases[position];
			position--; 
			counter++;
			break;*/
		/*case backward_half:
			if (position < 1)
			{
				position = 7;
			}
			PORTA = phases[position];
			position--;
			counter++;
			break;
		case backward_full:
			if (position < 1)
			{
				position = 7;
			}
			PORTA = phases[position];
			position--;
			counter++;
			break;*/
		default: 
			break;
	}
}

int main(void)
{
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as inputs
	DDRA = 0xFF; PORTA = 0x00; // Configure port A's 8 pins as inputs
	DDRD = 0xF0; PORTD = 0x0F; 
	DDRC = 0xFF; PORTC = 0x00; 
	TimerSet(3);
	TimerOn();
	sm_state = INIT;
	while(1)
	{	
		direction = GetKeypadKey();
		//PORTC = 0xFF; 
		TickFct_part1();
		while(!TimerFlag);
		TimerFlag = 0;
	}
}
