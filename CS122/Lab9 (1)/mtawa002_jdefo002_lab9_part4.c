/*	Partner(s) Name & E-mail: Marcel Tawamba & mtawa002@ucr.edu
 *	Partner(s) Name & E-mail: Joshua DeForest-Williams & jdefo002@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab # 9  Exercise # 4
 *	Expand upon part 3 of the lab by allowing the user to decide the direction of the rotation.
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

enum SM_States{INIT, wait_input, debounce, forward, backward} sm_state;
char position = 0;
int numPhases = 0; 
int value = 0;
int counter = 0; 
char phases[] = {0x01, 0x03,0x02, 0x06, 0x04, 0x0C, 0x08, 0x09}; //A, AB, B, BC, C, CD, D, DA
unsigned char input = 0;
void TickFct_part1(){
	input = GetKeypadKey(); 
	//PORTC  = input;
	switch(sm_state){
		case INIT:
			sm_state = wait_input;
			break;
		case wait_input:
			if (input != '\0' && input != 'A' && input != 'B')
			{	
				sm_state = debounce;
				if(input < 65){
					PORTC  = input;
					value = value*10 + (input - 48);
					PORTC = value; 
				} 
			}
			else if (input == 'A' ){
				sm_state = forward; 
				numPhases = (value / 5.625 ) * 64;
				value = 0;
			}
			else if (input == 'B' ){
				sm_state = backward;
				numPhases = (value / 5.625 ) * 64;
				value = 0;
			}
			else if (input == '\0'){
				sm_state = wait_input;
			}
			break;
		case forward:
			if (counter <= numPhases){
				sm_state = forward;
			}
			else {
				sm_state = wait_input;
				counter = 0; 
			}
			break;	
		case backward:
			if (counter <= numPhases){
				sm_state = backward;
			}
			else {
				sm_state = wait_input;
				counter = 0;
			}
			break;
		case debounce:
			if (input != '\0'){
				sm_state = debounce;
			}
			else {
				sm_state = wait_input;
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
			counter++; 
			break;
		case backward:
			if (position < 1)
			{
				position = 7;
			}
			PORTA = phases[position];
			position--;
			counter++;
			break;
		case debounce:
			break;
		default: 
			break;
	}
}

int main(void)
{
	DDRA = 0xFF; PORTA = 0x00; // Configure port A's 8 pins as inputs
	DDRD = 0xF0; PORTD = 0x0F; 
	DDRC = 0xFF; PORTC = 0x00; 
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
