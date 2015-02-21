/*	Partner(s) Name & E-mail: Marcel Tawamba mtawa002@ucr.edu
 *  Partner(s) Name & E-mail: Joshua DeForest-Williams jdefo002@ucr.edu
 *	Lab Section: 022 
 *	Assignment: Lab # 6 Exercise # 3
 *	Exercise Description: Expand upon exercise 2 of the lab by adjusting the speed the illuminated 
 *		LED shifts depending on how far left or right the joystick is tilted. For example, if the 
 *		joystick is tilted only slightly to the right, the LED will move slower. However, if the 
 *		joystick is tilted all the way to the right, the LED will move much faster.
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

unsigned char pattern = 0x80;
unsigned char row = 0xEF;
unsigned char cnt_1, cnt_2, cnt_3, cnt_4;
enum SM_States{init, wait_tilt, move_left, move_right, speed_1, speed_2, speed_3, speed_4} SM_State;

void Tick_Fct(){
	unsigned short input = ADC;
	
	switch(SM_State){ //transitions
		case init:
			cnt_1 = 0;
			cnt_2 = 0;
			cnt_3 = 0;
			cnt_4 = 0;
			SM_State = wait_tilt;
			break;
			
		case wait_tilt:		
			if(input > 510 && input < 514){
				SM_State = wait_tilt;
			}else if(input > 514){
				SM_State = move_right;
			}else if(input < 510){
				SM_State = move_left;
			}
			break;
			
		case move_left:
			if(input > 400 && input < 510){
				cnt_1 = 0;
				SM_State = speed_1;
			}else if(input > 250 && input < 400){
				cnt_2 = 0;
				SM_State = speed_2;
			}else if(input > 100 && input < 250){
				cnt_3 = 0;
				SM_State = speed_3;
			}else if(input < 100){
				cnt_4 = 0;
				SM_State = speed_4;
			}
			else if(input > 510 && input < 514){
				SM_State = wait_tilt;
			}
			break;	
			
		case move_right:
			if(input > 514 && input < 650){
				cnt_1 = 0;
				SM_State = speed_1;
			}else if(input > 650 && input < 800){
				cnt_2 = 0;
				SM_State = speed_2;
			}else if(input > 800 && input < 950){
				cnt_3 = 0;
				SM_State = speed_3;
			}else if(input > 950){
				cnt_4 = 0;
				SM_State = speed_4;
			}
			else if(input > 510 && input < 514){
				SM_State = wait_tilt;
			}
			break;	
		
		case speed_1:
			if(cnt_1 < 20){
				SM_State = speed_1;
			}else if(!(cnt_1 < 20)&&(input > 514)){
				SM_State = move_right;
			}else if(!(cnt_1 < 20)&&(input < 510)){
				SM_State = move_left;
			}else if(!(cnt_1 < 20) && (input > 510 && input < 514)){
				SM_State = wait_tilt;
			}
			break;
		
		case speed_2:
			if(cnt_2 < 10){
				SM_State = speed_2;
			}else if(!(cnt_2 < 10)&&(input > 514)){
				SM_State = move_right;
			}else if(!(cnt_2 < 10)&&(input < 510)){
				SM_State = move_left;
			}else if(!(cnt_2 < 10) && (input > 510 && input < 514)){
				SM_State = wait_tilt;
			}
			break;
		
		case speed_3:
			if(cnt_3 < 5){
				SM_State = speed_3;
			}else if(!(cnt_3 < 5)&&(input > 514)){
				SM_State = move_right;
			}else if(!(cnt_3 < 5)&&(input < 510)){
				SM_State = move_left;
			}else if(!(cnt_3 < 5) && (input > 510 && input < 514)){
				SM_State = wait_tilt;
			}
			break;		
		
		case speed_4:
			if(cnt_4 < 2){
				SM_State = speed_4;
			}else if(!(cnt_4 < 2)&&(input > 514)){
				SM_State = move_right;
			}else if(!(cnt_4 < 2)&&(input < 510)){
				SM_State = move_left;
			}else if(!(cnt_4 < 2) && (input > 510 && input < 514)){
				SM_State = wait_tilt;
			}
			break;
		default:
			SM_State = init;
			break;
	}
	
	switch(SM_State){ //actions
		case wait_tilt:
			break;
		
		case move_left:
			if(pattern != 0x80){
				pattern <<= 1;
			}
			else {
				pattern = 0x01;
			}
			break;
		
		case move_right:
			if(pattern != 0x01){
				pattern >>= 1;
			}else{
				pattern = 0x80;
			}
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
	PORTC = pattern;
	PORTD = row;
}
int main(void)
{
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	SM_State = init;
	TimerSet(50);
	TimerOn();
	A2D_init();
	while(1)
	{
		Tick_Fct();
		while(!TimerFlag){}
		TimerFlag = 0;
	}
}