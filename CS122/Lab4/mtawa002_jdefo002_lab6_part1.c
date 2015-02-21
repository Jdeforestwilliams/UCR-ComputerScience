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

unsigned short input;

void A2D_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: Enables analog-to-digital conversion
	// ADSC: Starts analog-to-digital conversion
	// ADATE: Enables auto-triggering, allowing for constant
	//	    analog to digital conversions.
}

enum SM_States{init, input_1} SM_State;

void Tick_Fct(){
	input = ADC; // short is required to store all
	switch(SM_State){  //transitions
		case init:
		SM_State = input_1;
		break;
		
		case input_1 :
		SM_State = input_1; 
		break;
		
		default:
		SM_State = init;
		break;
	}
	
	switch(SM_State){ //actions
		case input_1:
			PORTB = input;
			PORTD = (input >> 8 );
		break;
		
		default:
		break;
	}
}

int main(void)
{
	DDRB = 0xFF; PORTB = 0x00; 
	DDRD = 0xFF; PORTD = 0x00; 
    
	SM_State = init;
    TimerSet(300);
    TimerOn();
	
    A2D_init();
	while(1)
    {
	    Tick_Fct();
	    while(!TimerFlag){}
	    TimerFlag = 0;		
    }
	return 0;
}