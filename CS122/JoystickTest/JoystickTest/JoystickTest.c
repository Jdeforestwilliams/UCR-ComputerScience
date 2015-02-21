/*	Partner(s) Name & E-mail: Marcel Tawamba mtawa002@ucr.edu
 *  Partner(s) Name & E-mail: Joshua DeFOrest-Williams jdefo002@ucr.edu
 *	Lab Section: 022 
 *	Assignment: Lab # 6 Exercise # 4
 *	Exercise Description: Design a system that moves an illuminated LED (controlled by the joystick) 
 *      around a 5x8 LED matrix. The LED can be moved up, down, left, right, up/left, up/right, down/left, 
 *      or down/right. An additional function is needed for this exercise to allow for switching to other 
 *      ADC channels to handle the additional axis.
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

void A2D_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: Enables analog-to-digital conversion
	// ADSC: Starts analog-to-digital conversion
	// ADATE: Enables auto-triggering, allowing for constant
	//	    analog to digital conversions.
}

void Set_A2D_Pin(unsigned char pinNum) {
	ADMUX = (pinNum <= 0x07) ? pinNum : ADMUX;
	// Allow channel to stabilize
	static unsigned char i = 0;
	for ( i=0; i<15; i++ ) { asm("nop"); }
}

//unsigned char pattern = 0x80;
//unsigned char row = 0xEF;
unsigned char cnt_1, cnt_2, cnt_3, cnt_4;
enum SM_States{init, wait_tilt, move_l, move_r, move_u, move_d, move_ul, move_ur, move_dl, move_dr, speed_1, speed_2, speed_3, speed_4 } SM_State;

void Tick_Fct(){
	Set_A2D_Pin(0x00);
	unsigned short input_lr = ADC;
	Set_A2D_Pin(0x01);
	unsigned short input_ud = ADC;
		
	switch(SM_State){ //transitions
		case init:
			SM_State = wait_tilt;
			break;
			
		case wait_tilt:
			if((input_lr > 510 && input_lr < 514) && (input_ud > 515 && input_ud < 524)){
				SM_State = wait_tilt;
			}else if((input_lr < 510) && (input_ud > 515 && input_ud < 524)){
				SM_State = move_l;
			}else if((input_lr > 514) && (input_ud > 515 && input_ud < 524)){
				SM_State = move_r;
			}else if((input_lr > 510 && input_lr < 514) && (input_ud < 515)){
				SM_State = move_d;
			}else if((input_lr > 510 && input_lr < 514) && (input_ud > 524)){
				SM_State = move_u;
			}else if(input_lr < 510 && input_ud < 515){
				SM_State = move_dl;
			}else if(input_lr < 510 && input_ud > 524){
				SM_State = move_ul;
			}else if(input_lr > 514 && input_ud < 515){
				SM_State = move_dr;
			}else if(input_lr > 514 && input_ud > 524){
				SM_State = move_ur;
			}
			break;
		case move_l:
		case move_r:
		case move_u:
		case move_d:
		case move_ul:
		case move_ur:
		case move_dl:
		case move_dr:
			break;			
		case speed_1:
			break;
		case speed_2:
			break;
		case speed_3:
			break; 
		case speed_4:
			break;	
		default:
			SM_State = init;
			break;
	}
	
	switch(SM_State){ //actions
		case wait_tilt:
			PORTB = 0x01; 
			//PORTD = 0x00;
			//PORTC = 0x00;
			break;
		
		case move_l:
			PORTB = 0x00;
			PORTD = 0x0C; 
			PORTC = 0x00;
			break;
		
		case move_r:
			PORTB = 0x00;
			PORTC = 0x0C; 
			PORTD = 0x00; 
			break;
		
		case move_u:
			PORTB = 0x00;
			PORTC = 0xC0;
			PORTD = 0x00;  
			break;
		
		case move_d:
			PORTB = 0x00;
			PORTD = 0xC0;
			PORTC = 0x00;
			break;
		
		case move_ul:
			PORTB = 0x00;
			PORTD = 0x03;
			PORTC = 0x00;
			break;
		
		case move_ur:
			PORTB = 0x00;
			PORTC = 0x30; 
			PORTD = 0x00;
			break;
		
		case move_dl:
			PORTB = 0x00;
			PORTD = 0x30;
			PORTC = 0x00;
			break;
		
		case move_dr:
			PORTB = 0x00;
			PORTC = 0x03;
			PORTD = 0x00;
			break;
		case speed_1:
			cnt_1++;
			break;
		case speed_2:
			cnt_2++;
			break;
		case speed_3:
			cnt_3++;
			break;
		case speed_4:
			cnt_4++;
			break;			
		default:
			break;
	}
}

int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00; 
	DDRD = 0xFF; PORTD = 0x00;
	
	SM_State = init;
	TimerSet(100);
	TimerOn();
	A2D_init();
	while(1)
	{
		Tick_Fct();
		while(!TimerFlag){}
		TimerFlag = 0;
	}
}