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
unsigned char pattern = 0xFF;
unsigned char row = 0xFE; 
enum SM_States{init, wait_input, row_up, row_down} SM_State;

void Tick_Fct(){
	unsigned char input = (~PINA) & 0x03;
	switch(SM_State){  //transitions
		case init:
			SM_State = wait_input;
			break;
			
		case wait_input:
		case row_up:
		case row_down:
			if(input == 0x01){
				SM_State = row_up;
			}else if(input == 0x02){
				SM_State = row_down;
			}else{
				SM_State = wait_input;
			}
			break;
		
		default:
			SM_State = init;
			break;
	}	
	
	switch(SM_State){ //actions
		case wait_input:
			break;
		
		case row_up:
			if(row != 0xEF){
				row = (row << 1) | 0x01;
			}
			break;
		
		case row_down:
			if(row != 0xFE){
				row = (row >> 1) | 0x80;
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
	DDRA = 0x00; PORTA = 0xFF;
	
    SM_State = init;
    TimerSet(300);
    TimerOn();
    while(1)
    {
	    Tick_Fct();
	    while(!TimerFlag){}
	    TimerFlag = 0;
    }
}