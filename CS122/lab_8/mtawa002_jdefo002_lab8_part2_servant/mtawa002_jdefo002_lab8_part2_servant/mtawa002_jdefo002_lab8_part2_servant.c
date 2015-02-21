#include <avr/io.h>
#include <avr/interrupt.h>
#include "spi.h"
#include "keypad.h"

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
unsigned char speeds[] = {40, 20, 10, 5, 2, 1};
unsigned char spd = 0;
unsigned char pttrn = 0;
unsigned char rcv = 0;
unsigned char seq = 0, cnt = 0;
unsigned char A[] = {0xF0, 0x0F};
unsigned char B[] = {0xAA, 0x55};
unsigned char D[] = {0xCC, 0x33};
unsigned char i = 0;
enum SM_States{INIT, wait_data, decision, bpt1_on, bpt1_off, bpt2_on, bpt2_off, bpt3_on, bpt3_off, bpt4_on, bpt4_off}sm_state;

void TickFct_part2(){
//	rcv = receivedData;
	 switch(sm_state){
		 case INIT:
			sm_state = wait_data;
			break;
		case wait_data:
			if(rcv == 0){
				sm_state = wait_data;
			} else{
				sm_state = decision;
				spd = rcv & 0x0F;
				pttrn = (rcv & 0xF0) >> 4;
			}
			break;
		case decision:
			if(rcv != receivedData || pttrn == 0){
				sm_state = wait_data;
			}else if(rcv == receivedData && pttrn == 1){
				cnt = 0;
				sm_state = bpt1_on;
			}else if(rcv == receivedData && pttrn == 2){		
				cnt = 0;
				sm_state = bpt2_on;
			}else if(rcv == receivedData && pttrn == 3){
				seq = 0x80;
				cnt = 0;
				sm_state = bpt3_on;
			}else if(rcv == receivedData && pttrn == 4){
				cnt = 0;
				sm_state = bpt4_on;
			}
			break;
		case bpt1_on:
			if(rcv != receivedData){
				sm_state = wait_data;
			}else{
				sm_state = bpt1_off;
				cnt = 0;
			}
			break;
		case bpt1_off:
			if(rcv != receivedData){
				sm_state = wait_data;
			}else if(cnt < speeds[spd] && rcv == receivedData){
				sm_state = bpt1_off;
			}else if(cnt >= speeds[spd] && rcv == receivedData){
				sm_state = bpt1_on;
				cnt = 0;
			}
			break;
		case bpt2_on:
			if(rcv != receivedData){
				sm_state = wait_data;
			}else {
				sm_state = bpt2_off;
				cnt = 0;
			}
			break;
		case bpt2_off:
			if(rcv != receivedData){
				sm_state = wait_data;
			}else if(cnt < speeds[spd] && rcv == receivedData){
				sm_state = bpt2_off;
			}else if(cnt >= speeds[spd] && rcv == receivedData){
				sm_state = bpt2_on;
				cnt = 0;
			}
			break;
		case bpt3_on:
			if(rcv != receivedData){
				sm_state = wait_data;
			}else {
				sm_state = bpt3_off;
				cnt = 0;
			}
			break;
		case bpt3_off:
			if(rcv != receivedData){
				sm_state = wait_data;
			}else if(cnt < speeds[spd] && rcv == receivedData){
				sm_state = bpt3_off;
			}else if(cnt >= speeds[spd] && rcv == receivedData){
				sm_state = bpt3_on;
			}
			break;
		case bpt4_on:
			if(rcv != receivedData){
				sm_state = wait_data;
			}else {
				sm_state = bpt4_off;
				cnt = 0;
			}
			break;
		case bpt4_off:
			if(rcv != receivedData){
				sm_state = wait_data;
			}else if(cnt < speeds[spd] && rcv == receivedData){
				sm_state = bpt4_off;
			}else if(cnt >= speeds[spd] && rcv == receivedData){
				sm_state = bpt4_on;
				cnt = 0;
			}
		break;
		default:
			sm_state = INIT;
			break;
	 }
	 
	 switch(sm_state){
		 case wait_data:
			rcv = receivedData;
			PORTD = 0x01; 
			break;
		case decision:
			PORTD = 0x02;
			break;
		case bpt1_on:
			PORTA = A[i%2];
			i++;
			PORTD = 0x03;
			break;
		case bpt1_off:
			cnt++;
			PORTD = 0x04;
			break;
		case bpt2_on:
			PORTA = B[i%2];
			i++;
			PORTD = 0x05;
			break;
		case bpt2_off:			
			cnt++;
			PORTD = 0x06;
			break;
		case bpt3_on:
			PORTA = seq;
			if(seq == 0x01) seq = 0x80;
			else seq = seq >> 1;
			PORTD = 0x07;
			break;
		case bpt3_off:
			cnt++;
			PORTD = 0x08;
			break;
		case bpt4_on:
			PORTA = D[i%2];
			i++;
			PORTD = 0x09;
			break;
		case bpt4_off:
			cnt++;
			PORTD = 0x0A;
			break;
		default:
			PORTD = 0x0B;
			break;
	 }
}

int main(void)
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRD = 0xFF; PORTD = 0x00; 
	TimerOn();
	TimerSet(50);
	SPI_ServantInit();
	while(1)
	{
		PORTD = 0x0F;  
		TickFct_part2();
		while(!TimerFlag);
		TimerFlag = 0;
	}
}