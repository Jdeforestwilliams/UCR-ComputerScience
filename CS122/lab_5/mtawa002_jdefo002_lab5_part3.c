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

unsigned char pattern[3] = {0x3C, 0x24, 0x3C};
unsigned char row[3] = {0xFD, 0xFB, 0xF7};
unsigned char ind = 0;

enum SM_States{init, row_2, row_3, row_4}SM_State;
void Tick_Fct(){
	switch(SM_State){ //transitions
		case init:
			SM_State = row_2;
			break;
		
		case row_2:
			SM_State = row_3;
			break;
		
		case row_3:
			SM_State = row_4;
			break;
		
		case row_4:
			SM_State =  row_2;
			break;
		
		default:
			SM_State = init;
			break;
	}	
	switch(SM_State){ //actions
		case row_2:
		case row_3:
		case row_4:
			PORTC = pattern[ind];
			PORTD = row[ind];
			ind = (ind + 1)%3;
			break;
			
		default:
			break;			
	}
}

int main(void)
{
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	SM_State = init;
	TimerSet(1);
	TimerOn();
	while(1)
	{
		Tick_Fct();
		while(!TimerFlag){}
		TimerFlag = 0;
	}
}