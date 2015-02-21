#include <avr/io.h>
#include <avr/interrupt.h>
#include "ADC_controller.h"
#include "usart_controller.h"

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1ms
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B 	= 0x0B;	// bit3 = 1: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: prescaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A 	= 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register

	TIMSK1 	= 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1 = 0;

	// TimerISR will be called every _avr_timer_cntcurr milliseconds
	_avr_timer_cntcurr = _avr_timer_M;

	//Enable global interrupts
	SREG |= 0x80;	// 0x80: 1000000
}

void TimerOff() {
	TCCR1B 	= 0x00; // bit3bit2bit1bit0=0000: timer off
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect)
{
	// CPU automatically calls when TCNT0 == OCR0 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; 			// Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { 	// results in a more efficient compare
		TimerISR(); 				// Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
typedef struct task {
	int state;
	unsigned long period;
	unsigned long elapsedTime;
	int (*TickFct)(int);
} task;

task tasks[3];
const unsigned char tasksNum = 3;
const unsigned long periodMode = 100;
//const unsigned long periodStop = 100;
const unsigned long periodJoystick = 100;
const unsigned long periodsend = 50;

const unsigned tasksPeriodGCD = 50;

void TimerISR() {
	TimerFlag = 1;
	unsigned char i;
	for (i = 0; i < tasksNum; ++i) { // Heart of scheduler code
		if ( tasks[i].elapsedTime >= tasks[i].period ) { // Ready
			tasks[i].state = tasks[i].TickFct(tasks[i].state);
			tasks[i].elapsedTime = 0;
		}
		tasks[i].elapsedTime += tasksPeriodGCD;
	}
}

enum mode_states{init_1, free_mode, controlled_mode, wait_1, wait_2};
unsigned char mode = 0xFF;//mode in which the car is in
int TickFct_mode(int state){
	unsigned char x = (~PINB) & 0x01;
	switch(state){//transitions
		case init_1:
		state = free_mode;
		break;
		
		case free_mode:
		if(x == 0x00){
			state = wait_1;
			}else{
			state = free_mode;
		}break;
		
		case wait_1:
		if(x == 0x00){
			state = wait_1;
			}else{
			state = controlled_mode;
		}break;
		
		case controlled_mode:
		if (x == 0x00){
			state = wait_2;
			}else{
			state = controlled_mode;
		}break;
		
		case wait_2:
		if(x == 0x00){
			state = wait_2;
			}else{
			state = free_mode;
		}break;
		
		default:
		state = init_1;
		break;
	}
	switch(state){//actions
		case free_mode:
		mode = 0x00;
		break;
		
		case controlled_mode:
		mode = 0xFF;
		break;
		
		case wait_2:
		case wait_1:
		break;
		
		default:
		break;
	}
	return state;
}

enum joystick_states{init_2, direction_in};
//limits for the joystick
const unsigned short upLeft_limit = 5;
const unsigned short downRight_limit = 1000;
//ADC values to be used
unsigned short LeftRight;
unsigned short UpDown;
//global variable to be sent through USART
unsigned char direction = 0x00;

int TickFct_Joystick(int state)
{
	Set_A2D_Pin(0x00);
	LeftRight = ADC + 2;
	Set_A2D_Pin(0x01);
	UpDown = ADC + 2;
	switch(state)//Transitions
	{
		case init_2:
		state = direction_in;
		break;
		
		case direction_in:
		
		if((LeftRight < upLeft_limit) && !(LeftRight > downRight_limit))//Up
		{
			direction = 0x01;
		}
		else if((LeftRight > downRight_limit) && !(LeftRight < upLeft_limit))//Down
		{
			direction = 0x02;
		}
		else if((UpDown < upLeft_limit) && !(UpDown > downRight_limit))//Left
		{
			direction = 0x04;
		}
		else if((UpDown > downRight_limit) && !(UpDown < upLeft_limit))//Right
		{
			direction = 0x08;
		}else{
			direction = 0x0A;
		}
		
		state = direction_in;
		break;
		
		default:
		state = init_2;
		break;
	}
	
	switch(state)//actions
	{
		case direction_in:
		break;
		default:
		break;
	}
	return state;
}

enum send_states{init_3, dont_send, do_send};
int TickFct_send(state){
	switch(state){//transitions
		case init_3:
		state = dont_send;
		break;
		
		case dont_send:
		case do_send:
		if(mode == 0x00){
			state = dont_send;
			}else{
			state = do_send;
		}break;
		
		default:
		state = init_3;
		break;
	}
	
	switch(state){//actions
		case dont_send:
		if(USART_IsSendReady(0)){
			USART_Send(0xFF, 0);//free_mode
		}
		break;
		
		case do_send:
		if(USART_IsSendReady(0)){
			USART_Send(direction, 0);
		}
		break;
	}
	return state;
}

int main(void)
{
	DDRB = 0x00; PORTB = 0xFF;
	unsigned char i = 0;
	
	tasks[i].state = init_1;
	tasks[i].period = periodMode;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &TickFct_mode;
	
	++i;
	tasks[i].state = init_2;
	tasks[i].period = periodJoystick;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &TickFct_Joystick;

	++i;
	tasks[i].state = init_3;
	tasks[i].period = periodsend;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &TickFct_send;
	
	ADC_init();
	initUSART(0);
	
	TimerSet(tasksPeriodGCD);
	TimerOn();
	
	while(1);
	
	return 0;
}