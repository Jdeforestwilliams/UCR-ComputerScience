/*
 * mtawa002_jdefo002_lab4_part_1.c
 *
 * Created: 10/15/2014 10:59:57 PM
 *  Author: JDeForestWilliams
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;

typedef struct task {
	int state;
	unsigned long period;
	unsigned long elapsedTime;
	int (*TickFct)(int);
} task;

task tasks[5];

const unsigned char tasksNum = 5;
const unsigned long tasksPeriodGCD = 100;
const unsigned long periodIncrement = 500;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

unsigned char output = 0x00; //counter variable to be output

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

unsigned char SM1_Clk;
void TimerISR() {
	SM1_Clk = 1;
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
	int i;
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

enum SM1_States { SM1_intial, SM1_increment, SM1_waiting, SM1_decrement, SM1_Both, SM1_Transfer_Wait } SM1_State;

int TickFct_State_machine_1() {
	switch(SM1_State) { // Transitions
		case -1:
		SM1_State = SM1_intial;
		break;
		case SM1_intial:
		if (1) {
			SM1_State = SM1_waiting;
		}
		break;
		case SM1_increment:
		if (1) {
			SM1_State = SM1_Transfer_Wait;
		}
		break;
		case SM1_waiting:
		if (!(PINA & 0x01) && !(PINA & 0x02)) {
			SM1_State = SM1_waiting;
		}
		else if ( (PINA & 0x01) && !(PINA & 0x02) && !(output > 255)) {
			SM1_State = SM1_increment;
		}
		else if (!(PINA & 0x01) && (PINA & 0x02) && !(output==0)) {
			SM1_State = SM1_decrement;
		}
		else if ((PINA & 0x01) && (PINA & 0x02)) {
			SM1_State = SM1_Both;
		}
		break;
		case SM1_decrement:
		if (1) {
			SM1_State = SM1_Transfer_Wait;
		}
		break;
		case SM1_Both:
		if (1) {
			SM1_State = SM1_waiting;
		}
		break;
		case SM1_Transfer_Wait: 
		if (transmit_wait > 5){
			SM1_State = SM1_waiting
		}
		else if (transmit_wait < 5){
			SM1_State = SM1_Transfer_Wait
		}
		break;
		default:
		SM1_State = SM1_intial;
	} // Transitions

	switch(SM1_State) { // State actions
		case SM1_intial:
		output= 0; 
		break;
		case SM1_increment:
		output++;
		transmit_data(output);
		break;
		case SM1_waiting:
		break;
		case SM1_decrement:
		output--;
		transmit_data(output);
		break;
		case SM1_Transfer_Wait:
		transmit_wai
		case SM1_Both:
		output= 0x00;
		transmit_data(output);
		break;
		default: // ADD default behaviour below
		break;
	} // State actions
	
}
int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs,
	unsigned char i = 0;
	tasks[i].state = SM1_intial;
	tasks[i].period = periodIncrement;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &TickFct_State_machine_1;
	
	TimerSet(tasksPeriodGCD);
	TimerOn();
    while(1)
    {
		TickFct_State_machine_1();
		while(!SM1_Clk);
		SM1_Clk = 0;
    }
}