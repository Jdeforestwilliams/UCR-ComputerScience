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

unsigned char cnt = 0;
unsigned char data = 0;
enum SM_States{INIT, follow, check, lead} SM_State;
void TickFct_leadFollow(){
	switch(SM_State){//transitions
		case INIT:
			SM_State = follow;
			break;
		case follow:
			SM_State = check;
			cnt = 0;
			break;

		case check:
			if(!USART_HasReceived(0) && cnt < 6){
				SM_State = check;
			}else if(USART_HasReceived(0) && cnt < 6){
				PORTA = USART_Receive(0);
				SM_State = follow;
			}else if(!(cnt < 6)){
				SM_State = lead;
			}
			break;

		case lead:
			if(!USART_HasReceived(0)){
				SM_State = lead;
			}else{
				PORTA = USART_Receive(0);
				SM_State = follow;
				PORTC = 0x00;
			}
			break;

		default:
			SM_State = INIT;
			break;
	}

	switch(SM_State){//actions
		case follow:
			PORTC = 0x00;
			break;

		case check:
			cnt++;
			break;

		case lead:
			PORTC = 0x01;
			if(USART_IsSendReady(0)){
				USART_Send(data, 0);
			}
			PORTA = data;
			data = (data+1)%2;
			break;

		default:
			break;
	}
}

int main(void)
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRB = 0xFE; PORTB = 0x01;
	initUSART(0); // Initialize USART0
	SM_State = INIT;
	TimerSet(500);
	TimerOn();
    while(1)
    {
		TickFct_leadFollow();
		while(!TimerFlag){}
		TimerFlag = 0;  
    }
}