/*	Partner(s) Name & E-mail:Marcel Tawamba & mtawa002@ucr.edu
 *	Partner(s) Name & E-mail:Joshua DeForest-Williams & jdefo002@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab # 7  Exercise # 1 
 *	Exercise Description: Two microcontrollers each have an LED connected to PA0. Both     
 * 	LEDs are synchronously toggled on/off in one second intervals using USART.
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//Follower

#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart_ATmega1284.h"

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

//unsigned char count = 0;
unsigned char temp = 0; 

enum Status_States { off, on } SM_State;
void TickFct_Status() {
	switch(SM_State) { // Transitions
		case off: // Initial transition
			SM_State = on;
			break;
		case on:
			SM_State = off;
			break;
		default:
			SM_State = off;
			break;
	}

	switch(SM_State) { // State actions
		case off:
			while(!USART_HasReceived(0));
			temp = USART_Receive(0);
			USART_Flush(0);
			PORTA = temp;
			break;
		case on:
			while(!USART_HasReceived(0));
			temp = USART_Receive(0);
			USART_Flush(0);
			PORTA = temp;
			break;
		default:
			break;
	}
}

int main(void)
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	//DDRD = 0x00; PORTD = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	initUSART(0); // Initialize USART0
	SM_State = off;
	TimerSet(10);
	TimerOn();
	while(1)
	{
		TickFct_Status();
		while(!TimerFlag){}
		TimerFlag = 0;
	}
}