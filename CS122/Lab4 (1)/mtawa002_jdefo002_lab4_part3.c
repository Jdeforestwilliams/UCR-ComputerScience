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

unsigned char sequence1;
unsigned char sequence2;
unsigned char sequence3;


void transmit_data_to_B(unsigned char data) {
	int i;
	for (i = 7; i >= 0 ; --i) {
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		PORTB = 0x08;
		// set SER = next bit of data to be sent.
		PORTB |= ((data >> i) & 0x01);
		// set SRCLK = 1. Rising edge shifts next bit of data into the shift register
		PORTB |= 0x04;
	}
	// set RCLK = 1. Rising edge copies data from the ?Shift? register to the ?Storage? register
	PORTB |= 0x02;
	// clears all lines in preparation of a new transmission
	PORTB = 0x00;
}
void transmit_data_to_C(unsigned char data) {
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
	// set RCLK = 1. Rising edge copies data from the ?Shift? register to the ?Storage? register
	PORTC |= 0x02;
	// clears all lines in preparation of a new transmission
	PORTC = 0x00;
}


enum SM1_States {SM1_INIT, SM1_s1 } SM1_State;

void TickFct_1() {
	static unsigned cnt1 = 0;
	static unsigned sequence[] = {0x81, 0x42,0x24, 0x18,0x24, 0x42};
	static unsigned size1 = sizeof(sequence)/sizeof(sequence[0]);
	switch(SM1_State) { // Transitions
		case SM1_INIT:
		SM1_State = SM1_s1;
		break;
		case SM1_s1:
		break;
		default:
		SM1_State = SM1_INIT;
	} // Transitions

	switch(SM1_State) { // State actions
		case SM1_s1:
		sequence1 = sequence[cnt1];
		cnt1 = (cnt1 >= (size1 - 1) ? 0 : cnt1 + 1);
		break;
		default: // ADD default behavior below
		break;
	} // State actions
}

enum SM2_States {SM2_INIT, SM2_s1 } SM2_State;

void TickFct_2() {
	static unsigned cnt2 = 0;
	static unsigned sequence[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
	static unsigned size2 = sizeof(sequence)/sizeof(sequence[0]);
	switch(SM2_State) { // Transitions
		case SM2_INIT:
		SM2_State = SM2_s1;
		break;
		case SM2_s1:
		break;
		default:
		SM2_State = SM2_INIT;
	} // Transitions

	switch(SM2_State) { // State actions
		case SM2_s1:
		sequence2 = sequence[cnt2];
		cnt2 = (cnt2 >= (size2 - 1) ? 0 : cnt2 + 1);
		break;
		default: // ADD default behaviour below
		break;
	} // State actions
}

enum SM3_States {SM3_INIT, SM3_s1 } SM3_State;

void TickFct_3() {
	static unsigned cnt3 = 0;
	static unsigned sequence[] = {0xA5, 0x5A};
	static unsigned size3 = sizeof(sequence)/sizeof(sequence[0]);
	switch(SM3_State) { // Transitions
		case SM3_INIT:
		SM3_State = SM3_s1;
		break;
		case SM3_s1:
		break;
		default:
		SM3_State = SM3_INIT;
	} // Transitions

	switch(SM3_State) { // State actions
		case SM3_s1:
		sequence3 = sequence[cnt3];
		if(cnt3 >= (size3 - 1)){
			cnt3 = 0;
		}
		else{
			cnt3++;
		}
		break;
		default: // ADD default behaviour below
		break;
	} // State actions
}

enum SM4_States {SM4_INIT, SM4_sequence1, SM4_Depress, SM4_Off, SM4_Depress1, SM4_On } SM4_State;

void TickFct_TransitionB() {
	static unsigned cnt = 0;
	unsigned char tmpA2 = (~PINA & 0x04);
	unsigned char tmpA3 = (~PINA & 0x08);

	switch(SM4_State) { // Transitions
		case SM4_INIT:
		SM4_State = SM4_sequence1;
		break;
		case SM4_sequence1:
		if (!tmpA3 && tmpA2) {
			SM4_State = SM4_Depress;
			cnt = (cnt == 0 ? 2 : cnt - 1);
		}
		else if (tmpA3 && !tmpA2) {
			SM4_State = SM4_Depress;
			cnt = (cnt == 2 ? 0 : cnt + 1);
		}
		else if (tmpA3 && tmpA2) {
			SM4_State = SM4_Off;
		}
		else {
			SM4_State = SM4_sequence1;
		}
		break;
		case SM4_Depress:
		if (!tmpA3 && !tmpA2) {
			SM4_State = SM4_sequence1;
		}
		else {
			SM4_State = SM4_Depress;
		}
		break;
		case SM4_Off:
		if (tmpA3 && tmpA2) {
			SM4_State = SM4_Off;
		}
		else if (!tmpA3 && !tmpA2) {
			SM4_State = SM4_Depress1;
		}
		break;
		case SM4_Depress1:
		if (!tmpA3 && !tmpA2) {
			SM4_State = SM4_Depress1;
		}
		else if (tmpA3 && tmpA2) {
			SM4_State = SM4_On;
		}
		break;
		case SM4_On:
		if (tmpA3 && tmpA2) {
			SM4_State = SM4_On;
		}
		else if (!tmpA3 && !tmpA2) {
			SM4_State = SM4_sequence1;
		}
		break;
		default:
		SM4_State = SM4_sequence1;
	} // Transitions

	switch(SM4_State) { // State actions
		case SM4_sequence1:
		if(cnt == 0){ transmit_data_to_B(sequence1);}
		else if (cnt == 1) {transmit_data_to_B(sequence2); }
		else if (cnt == 2) {transmit_data_to_B(sequence3);}
		break;
		case SM4_Depress:
		break;
		case SM4_Off:
		transmit_data_to_B(0x00);
		break;
		case SM4_Depress1:
		break;
		case SM4_On:
		break;
		default: // ADD default behaviour below
		break;
	} // State actions
}

enum SM5_States {SM5_INIT, SM5_sequence1, SM5_Depress, SM5_Off, SM5_Depress1, SM5_On } SM5_State;

void TickFct_TransitionC() {
	static unsigned cnt = 0;
	unsigned char tmpA0 = (~PINA & 0x01);
	unsigned char tmpA1 = (~PINA & 0x02);

	switch(SM4_State) { // Transitions
		case SM5_INIT:
		SM4_State = SM5_sequence1;
		break;
		case SM5_sequence1:
		if (!tmpA1 && tmpA0) {
			SM5_State = SM5_Depress;
			cnt = (cnt == 0 ? 2 : cnt - 1);
		}
		else if (tmpA1 && !tmpA0) {
			SM5_State = SM5_Depress;
			cnt = (cnt == 2 ? 0 : cnt + 1);
		}
		else if (tmpA1 && tmpA0) {
			SM5_State = SM5_Off;
		}
		else {
			SM5_State = SM5_sequence1;
		}
		break;
		case SM5_Depress:
		if (!tmpA1 && !tmpA0) {
			SM5_State = SM5_sequence1;
		}
		else {
			SM5_State = SM5_Depress;
		}
		break;
		case SM5_Off:
		if (tmpA1 && tmpA0) {
			SM5_State = SM5_Off;
		}
		else if (!tmpA1 && !tmpA0) {
			SM5_State = SM5_Depress1;
		}
		break;
		case SM5_Depress1:
		if (!tmpA1 && !tmpA0) {
			SM5_State = SM5_Depress1;
		}
		else if (tmpA1 && tmpA0) {
			SM5_State = SM5_On;
		}
		break;
		case SM5_On:
		if (tmpA1 && tmpA0) {
			SM5_State = SM5_On;
		}
		else if (!tmpA1 && !tmpA0) {
			SM5_State = SM5_sequence1;
		}
		break;
		default:
		SM5_State = SM5_sequence1;
	} // Transitions

	switch(SM5_State) { // State actions
		case SM5_sequence1:
		if(cnt == 0){ transmit_data_to_C(sequence1);}
		else if (cnt == 1) {transmit_data_to_C(sequence2); }
		else if (cnt == 2) {transmit_data_to_C(sequence3);}
		break;
		case SM5_Depress:
		break;
		case SM5_Off:
		transmit_data_to_C(0x00);
		break;
		case SM5_Depress1:
		break;
		case SM5_On:
		break;
		default: // ADD default behaviour below
		break;
	} // State actions
}
int main() {
	
	DDRA = 0x00; PORTA = 0xFF; //Input
	DDRB = 0xFF; PORTB = 0x00; //output
	DDRC = 0xFF; PORTC = 0x00; //Output
	
	
	TimerSet(500);
	TimerOn();
	
	SM1_State = SM1_INIT;
	SM2_State = SM2_INIT;
	SM3_State = SM3_INIT;
	SM4_State = SM4_INIT;
	SM5_State = SM5_INIT;
	
	while(1) {
		TickFct_1();
		TickFct_2();
		TickFct_3();
		TickFct_TransitionC();
		TickFct_TransitionB();
		
		while (!TimerFlag);
		TimerFlag = 0;
	}
}