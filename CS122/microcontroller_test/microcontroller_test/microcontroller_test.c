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
enum SM_States{ wait, input} SM_State;

void Tick_Fct(){
	switch(SM_State){  //transitions
		case wait:
			SM_State = wait; 
			break;
		case input:
			SM_State = wait; 
			break;
		
		default:
			SM_State = wait;
			break;
	}
	
	switch(SM_State){ //actions
		case wait:
			PORTA = 0x01; 
			break;
		
		case off:
			PORTA = 0x00; 
			break;
		default:
		break;
	}

}
int main(void)
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRD = 0xF0; PORTD = 0x0F; 
	SM_State = wait;
	TimerSet(3);
	TimerOn();
	while(1)
	{
		Tick_Fct();
		while(!TimerFlag){}
		TimerFlag = 0;
	}
}