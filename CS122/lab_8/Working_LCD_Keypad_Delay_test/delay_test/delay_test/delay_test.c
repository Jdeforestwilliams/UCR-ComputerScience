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
#include <string.h>

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
	DDRA = 0xFF; PORTA = 0x00; 

	TimerSet(100);
	TimerOn();
	LCD_init(); 
	unsigned char key_input; 
	unsigned char ptrn[] = "Ptrn: ";
	unsigned char spd[] = "Spd: ";
	unsigned char uC[] = "uC: ";
	unsigned char space[] = " ";
	while(1)
	{
		key_input = GetKeypadKey();
		unsigned char data[2] = {key_input, 0x20};
		LCD_DisplayString(1, ptrn);
		LCD_DisplayString(7, data);	//needs to be masked for pattern
		LCD_DisplayString(9, spd);
		LCD_DisplayString(14, data);//needs to be masked for pattern
		LCD_DisplayString(17, uC); 
		LCD_DisplayString(21, data);//needs to be masked for pattern
		for (int i = 15; i < 17; i++){
			LCD_DisplayString(i,space);
		}
		for (int i = 23; i < 33; i++){
			LCD_DisplayString(i,space);
		}
		//LCD_DisplayString(7, string4);		
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 0;
}