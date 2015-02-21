/*	Partner(s) Name & E-mail: Marcel Tawamba mtawa002@ucr.edu
 *  Partner(s) Name & E-mail: Joshua DeForest-Williams jdefo002@ucr.edu
 *	Lab Section: 022 
 *	Assignment: Lab # 6 Exercise # 1
 *	Exercise Description: Design a system where the 10-bit binary result from an A2D conversion is 
 *		displayed on a bank of 10 LEDs. Use the Joystick to adjust the supplied voltage to PA0.
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

unsigned short input;

void A2D_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: Enables analog-to-digital conversion
	// ADSC: Starts analog-to-digital conversion
	// ADATE: Enables auto-triggering, allowing for constant
	//	    analog to digital conversions.
}

void Tick_Fct(){
	input = ADC; 
	PORTC = (char)input;
	PORTD = ( char)(input >> 8);
}

int main(void)
{
	DDRC = 0xFF; PORTC = 0x00; 
	DDRD = 0xFF; PORTD = 0x00; 
	
    /*TimerSet(100);
    TimerOn();*/
	
    A2D_init();
	while(1)
    {
	    Tick_Fct();
	    /*while(!TimerFlag){}
	    TimerFlag = 0;	*/
    }
	return 0;
}