/*	Partner(s) Name & E-mail:Marcel Tawamba & mtawa002@ucr.edu
 *	Partner(s) Name & E-mail:Joshua DeForest-Williams & jdefo002@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab # 8  Exercise # 1 Servant
 *	Exercise Description: In the ATmega1284 datasheet, search for “serial peripheral interface”. 
 *  The datasheet can be found in Student Materials -> labs -> datasheets. The first hit will be 
 *  the section “Serial Peripheral Interface - SPI”. Use the SPI section to fill out the code outline
 *  below. 
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
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
	DDRA = 0xFF; PORTA = 0x00;
	TimerOn();
	TimerSet(1000);
	SPI_ServantInit();
    while(1)
    {		
		PORTA = receivedData;
		while(!TimerFlag);
		TimerFlag = 0;
    }
}