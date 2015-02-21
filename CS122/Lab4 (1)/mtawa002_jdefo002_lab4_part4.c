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

unsigned short data = 0x0001;

void transmit_data(unsigned short data) {
	int i;
	for (i = 15; i >= 0 ; --i) {
		PORTC = 0x08;
		PORTC |= ((data >> i) & 0x01);
		PORTC |= 0x04;
	}
	PORTC |= 0x02;
	PORTC = 0x00;
}

enum DaisyTransmittor_States {INIT, DaisyTransmittor_forward, DaisyTransmittor_backward } DaisyTransmittor_State;

void TickFct_TransmittorDaisy() {
	switch(DaisyTransmittor_State) { // Transitions
		case INIT:
		DaisyTransmittor_State = DaisyTransmittor_forward;
		break;
		case DaisyTransmittor_forward:
		if (data != 0x8000) {
			DaisyTransmittor_State = DaisyTransmittor_forward;
			data = data << 1;
		}
		else if (!(data != 0x8000)) {
			DaisyTransmittor_State = DaisyTransmittor_backward;
			data = data >> 1;
		}
		break;
		case DaisyTransmittor_backward:
		if (data != 0x0001) {
			DaisyTransmittor_State = DaisyTransmittor_backward;
			data = data >> 1;
		}
		else if (!(data != 0x0001)) {
			DaisyTransmittor_State = DaisyTransmittor_forward;
			data = data << 1;
		}
		break;
		default:
		DaisyTransmittor_State = DaisyTransmittor_forward;
	}

	switch(DaisyTransmittor_State) { // State actions
		case DaisyTransmittor_forward:
		transmit_data(data);
		break;
		case DaisyTransmittor_backward:
		transmit_data(data);
		break;
		default:
		break;
	} // State actions

}

int main() {

	DDRC = 0xFF; PORTC = 0x00; //Outputs
	const unsigned int periodTransmittorDaisy = 500;
	TimerSet(periodTransmittorDaisy);
	TimerOn();
	
	DaisyTransmittor_State = INIT;

	while(1) {
		TickFct_TransmittorDaisy();
		while(!TimerFlag);
		TimerFlag = 0;
	}
}