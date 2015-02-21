#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "timer.h"
#include "usart.h"

int read_ultrasonic(){
	int count = 0;
	PORTB = 0x00;		// Ping all ultrasonic for 10 us
	_delay_us(10);		     //
	PORTB = 0xFF;		// Set port A to LOW

	_delay_ms(1);		     // delay to wait for transmitter to die off
	for (int i=0;i < 10000;i++){ // Checking port in loop 10,000 times

		if (PIND & 0x40){	     // read PORTF pin 5 for echo pulse
			count++;	// count if still high count
		}
	}

	return count/58;
}

enum states{init, start, controlled, wait_impact, stop_car, turn_left, hold_direction, reset_direction} state;
int distance = 0;
int count = 0, count_1 = 0;
unsigned char direction = 0;
void Tick_Fct(){
	distance = read_ultrasonic();
	
	if (USART_HasReceived(0))
	{
		direction = USART_Receive(0);
		PORTC = direction;
	}
	
	switch(state){//transitions
		case init:
			state = start;
			break;
		
		case start:
			if(direction == 0xFF){
				state = wait_impact;
				}else{
				state = controlled;
			}break;
			
		case controlled:
			if(direction == 0xFF){
				state = wait_impact;
			}else{
				count_1 = 0;	
				state = hold_direction;
			}break;
		
		case hold_direction:
			if(count_1 < 30){
				state = hold_direction;
			}else{
				state = reset_direction;
			}
			break;
		
		case reset_direction:
			state = controlled;
			break;
			
		case wait_impact:
			if (direction != 0xFF)
			{
				state = controlled;
			}
			else if(direction == 0xFF && distance > 30){
				state = wait_impact;
				}else {
				state = stop_car;
				count  = 0;
				PORTA = 0x00;
			}
			break;
		
		case stop_car:
			if (direction != 0xFF)
			{
				state = controlled;
			}
			else if(direction == 0xFF && count < 100){
				state = stop_car;
			}
			else if(direction == 0xFF && !(count < 100)){
				state = turn_left;
				count = 0;
			}
			break;
		
		case turn_left:
			if (direction != 0xFF)
			{
				state = controlled;
			}
			else if(direction == 0xFF && count < 100){
				state = turn_left;
			}
			else if(direction == 0xFF && !(count < 100)){
				state = wait_impact;
			}
			break;
		
		default:
			state = init;
			break;
	}
	
	switch(state){//actions
		case wait_impact:
			PORTA = 0x04;
			break;
		
		case stop_car:
			count++;
			PORTA = 0x42;
			break;
		
		case turn_left:
			count++;
			PORTA = 0x24;
			break;
		
		case start:
			PORTA = 0x00;
			break;
		
		case controlled:
			if(direction == 0x0A){
				PORTA = 0x00;
			}else if (direction == 0x01){
				PORTA = 0x44;//forward
			}else if (direction == 0x02){//reverse or backward
				PORTA = 0x42;
			}else if (direction == 0x04){//left
				PORTA = 0x24;
			}else if(direction == 0x08){//right
				PORTA = 0x44;
			}
			break;
			
		case hold_direction:
			count_1++;
			break;
		case reset_direction:
			PORTA = 0x00;
			break;
			
		default:
			break;
	}
}

int main(void)
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xBF; PORTD = 0x40;
	TimerSet(10);
	TimerOn();
	initUSART(0);
	state = init;
	while(1)
	{
		Tick_Fct();
		while(!TimerFlag);
		TimerFlag = 0;
	}
}