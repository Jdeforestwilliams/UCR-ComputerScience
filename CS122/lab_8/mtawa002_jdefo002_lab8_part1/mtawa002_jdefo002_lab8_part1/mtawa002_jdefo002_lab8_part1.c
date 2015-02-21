/*
 * mtawa002_jdefo002_lab8_part1.c
 *
 * Created: 11/6/2014 7:45:00 PM
 *  Author: student
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "spi.h"

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
	//DDRB = 0xFF; PORTB = 0x00;
	TimerOn();
	TimerSet(1000);
	unsigned char data = 0;
	SPI_MasterInit();
    while(1)
    {
		if (data < 255) data++;
		SPI_MasterTransmit(data);
		while(!TimerFlag);
		TimerFlag = 0;
    }
}