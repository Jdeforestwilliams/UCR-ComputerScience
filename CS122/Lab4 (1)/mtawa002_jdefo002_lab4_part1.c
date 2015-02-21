/*	mtawa002_jdefo002_lab4_part1.c - 10/16/2014
 *	Name & E-mail: Marcel   - 
 *	CS Login: 
 *	Partner(s) Name & E-mail:  - 
 *	Lab Section: 
 *	Assignment: Lab #  Exercise # 
 *	Exercise Description:
 *	
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

void transmit_data(unsigned char data) {
	signed char i;
	for (i = 7; i >= 0 ; --i) {
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		PORTC = 0x08;
		// set SER = next bit of data to be sent.
		PORTC |= ((data >> i) & 0x01);
		// set SRCLK = 1. Rising edge shifts next bit of data into the shift register
		PORTC |= 0x04;
	}
	// set RCLK = 1. Rising edge copies data from the “Shift” register to the “Storage” register
	PORTC |= 0x02;
	// clears all lines in preparation of a new transmission
	PORTC = 0x00;
}

unsigned char data = 0x00;

enum SM_states {INIT, wait_press, increment, decrement, wait_release, reset} state;

void TickFct_shift(){
	unsigned char input = (~PINA) & 0x03;
	switch(state){ //transitions
		case INIT:
			state = wait_press;
			transmit_data(0x00);
			//PORTD = 0x00;
			break;

		case wait_press:
			if(input == 0x00){
				state = wait_press;
			}else if(input == 0x01){
				state = increment;
			}else if(input == 0x02){
				state = decrement;
			}else if(input == 0x03){
				state = reset;
			}
			break;

		case increment:
		case decrement:
			state = wait_release;
			break;

		case wait_release:
			if(input == 0x00){
				state = wait_press;
			}else if(input == 0x03){
				state = reset;
			}else{
				state = wait_release;
			}
			break;

		case reset:
			state = wait_press;
			break;

		default:
			state = INIT;
			break;
	}
	switch(state){//actions
		case wait_press:
		case wait_release:
			break;

		case increment:
			if(data < 255){
				data++;	
			}
			transmit_data(data);
			//PORTD = data;
			break;

		case decrement:
			if(data > 0){
				data--;
			}
			transmit_data(data);
			//PORTD = data;
			break;

		case reset:
			data = 0x00;
			transmit_data(data);
			//PORTD = data;
			break;

		default:
			break;
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs,
	DDRD = 0xFF; PORTD = 0x00;
	
	state = INIT;

	TimerSet(500);
	TimerOn();
    while(1)
    {
		TickFct_shift();
		while(!TimerFlag);
		TimerFlag = 0;
    }
	return 0;
}