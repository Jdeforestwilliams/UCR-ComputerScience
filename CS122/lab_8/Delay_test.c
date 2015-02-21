/*
 * Delay_test.c
 *
 * Created: 11/6/2014 5:30:04 PM
 *  Author: student
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "keypad.h"
#include "lcd.h"

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

int main(void)
{
	DDRC = 0xFF; PORTC = 0x00; // Configure port A's 8 pins as inputs
	DDRD = 0xF0; PORTD = 0x0F;
	DDRB = 0xFF; PORTB = 0x00;

	TimerSet(1000);
	TimerOn();
	LCD_init();
	LCD_DisplayString(1, "Hello");
	unsigned char data = 0;
	while(1)
	{
		//data = GetKeypadKey();
		/*LCD_DisplayString(1, "Hello");
		while(!TimerFlag);
		TimerFlag = 0;*/
	}
	return 0;
}