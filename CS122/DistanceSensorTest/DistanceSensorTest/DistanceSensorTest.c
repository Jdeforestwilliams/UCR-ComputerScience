/*
 * DistanceSensorTest.c
 *
 * Created: 12/4/2014 6:04:18 PM
 *  Author: JDeForestWilliams
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

enum SM_States{INIT, trigger, echo} sm_state;
int counter = 0;
void TickFct_part1(){
	switch(sm_state){ //transitions
		case INIT:
			sm_state = trigger;
			PORTA = 0xFF; 
			break;
		case trigger:
			if (counter>= 10){
				sm_state = echo;	
			}
			else{
				sm_state = trigger; 
			}
			break;
		case echo:
			sm_state = trigger;
			break;
		default :
			sm_state = INIT;
			break;
	}
	switch(sm_state){ //actions
		case INIT:
			break;
		case trigger:
			PORTC = 0xFF;
			counter++;  
			break;
		case echo:
			PORTA = (PINB*10)/58; 
			PORTC = 0x00;
			counter = 0;  
			break;
		default:
			break;
	}
}

int main(void)
{
	DDRA = 0xFF; PORTA = 0x00; // Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	//DDRD = 0xFF; PORTD = 0x00; 
	TimerSet(1);
	TimerOn();
	sm_state = INIT;
	while(1)
	{
		TickFct_part1();
		while(!TimerFlag);
		TimerFlag = 0;
	}
}
