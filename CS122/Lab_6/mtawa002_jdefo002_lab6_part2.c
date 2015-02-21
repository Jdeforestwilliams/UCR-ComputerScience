/*	Partner(s) Name & E-mail: Marcel Tawamba mtawa002@ucr.edu
 *  Partner(s) Name & E-mail: Joshua DeForest-Williams jdefo002@ucr.edu
 *	Lab Section: 022 
 *	Assignment: Lab # 6 Exercise # 2
 *	Exercise Description: Using the A2D result stored in ADC, design a system where an illuminated 
 *		LED is shifted left or right along the top row an LED matrix. For this part of the lab, 
 *		only use the L/R output from the joystick. Connect the LED matrix according to the diagram 
 *		and pinouts given below.
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>

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

void A2D_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: Enables analog-to-digital conversion
	// ADSC: Starts analog-to-digital conversion
	// ADATE: Enables auto-triggering, allowing for constant
	//	    analog to digital conversions.
}

unsigned char pattern = 0x80;
unsigned char row = 0xEF;
enum SM_States{init, wait_tilt, move_left, move_right} SM_State;

void Tick_Fct(){
	unsigned short input = ADC;
	
	switch(SM_State){ //transitions
		case init:
			SM_State = wait_tilt;
			break;
			
		case wait_tilt:
		case move_left:
		case move_right:
			if(input > 514){
				SM_State = move_right;
			}else if(input < 512){
				SM_State = move_left;
			}else{
				SM_State = wait_tilt;
			}
			break;
			
		default:
			SM_State = init;
			break;
	}
	
	switch(SM_State){
		case wait_tilt:
			break;
		
		case move_left:
			if(pattern != 0x80){
				pattern <<= 1;
			}
			else {
				pattern = 0x01;
			}
			break;
		
		case move_right:
			if(pattern != 0x01){
				pattern >>= 1;
			}else{
				pattern = 0x80;
			}
			break;
		
		default:
			break;
	}
	PORTC = pattern;
	PORTD = row;
}
int main(void)
{
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	SM_State = init;
	TimerSet(100);
	TimerOn();
	A2D_init();
	while(1)
	{
		Tick_Fct();
		while(!TimerFlag){}
		TimerFlag = 0;
	}
}