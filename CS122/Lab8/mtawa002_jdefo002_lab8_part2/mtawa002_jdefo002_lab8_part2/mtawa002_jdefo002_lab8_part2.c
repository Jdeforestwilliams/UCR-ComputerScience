#include <avr/io.h>
#include <avr/interrupt.h>
#include "spi.h"
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

enum SM_States{INIT, wait_pattern, detect_pattern, wait_speed, detect_speed, transmit}sm_state;
unsigned char data = 0;
unsigned char pttrn = 0;
unsigned char spd = 0;
unsigned char toSend = 0;
void TickFct_part2(){
	data = GetKeypadKey();
	switch(sm_state){
		case INIT:
			sm_state = wait_pattern;
			break;
			
		case wait_pattern:
			if(data == 0){
				sm_state = wait_pattern;
			} else{
				sm_state = detect_pattern;
			}
			break;
		
		case detect_pattern:
			data = 0;
			sm_state = wait_speed;
			break;
		
		case wait_speed:
			if(data == 0){
				sm_state = wait_speed;
			}else {
				sm_state = detect_speed;
			}
			break;
		
		case detect_speed:
			data = 0;
			sm_state = transmit;
			break;
		
		case transmit:
			sm_state = wait_pattern;
			break;
		
		default :
			sm_state = INIT;
			break;
	}
	switch(sm_state){
		case wait_pattern:
		case wait_speed:
			break;
			
		case detect_pattern:
			pttrn = data - 64;
			break;
		
		case detect_speed:
			spd = data - 48;
			break;
					
		case transmit:
			toSend = pttrn << 4;
			toSend = toSend | spd;
			SPI_MasterTransmit(toSend);
			break;
		
		default: 
			break;
	}
}

int main(void)
{
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as inputs
	DDRD = 0xF0; PORTD = 0x0F; // Configure port D's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as inputs
	//DDRA = 0xFF; PORTA = 0x00; // Configure port A's 8 pins as inputs
	TimerOn();
	TimerSet(100);
	SPI_MasterInit();
	unsigned char key_input;
	unsigned char ptrn1[] = "Ptrn: ";
	unsigned char spd1[] = "Spd: ";
	unsigned char uC[] = "uC: ";
	unsigned char space[] = " ";
	while(1)
	{		
		key_input = GetKeypadKey();
		//PORTA = key_input; 
		unsigned char data1[2] = {key_input, 0x20};
		LCD_DisplayString(1, ptrn1);
		LCD_DisplayString(7, data1);	//needs to be masked for pattern
		LCD_DisplayString(9, spd1);
		LCD_DisplayString(14, data1);//needs to be masked for pattern
		LCD_DisplayString(17, uC);
		LCD_DisplayString(21, data1);//needs to be masked for pattern
		for (int i = 15; i < 17; i++){
			LCD_DisplayString(i,space);
		}
		for (int i = 23; i < 33; i++){
			LCD_DisplayString(i,space);
		}
		TickFct_part2();
		while(!TimerFlag);
		TimerFlag = 0;
	}
}