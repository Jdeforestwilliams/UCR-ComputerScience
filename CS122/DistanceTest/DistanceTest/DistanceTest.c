#include <avr/io.h>
#include <avr/interrupt.h>
# define F_CPU 16000000UL
#include <util/delay.h>


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

int read_ultrasonic();

int main(void)
{
	DDRA = 0xFF; PORTA = 0x00; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0x00; PORTD = 0x00;
	short distance = 0; 
	TimerSet(50);
	TimerOn();
	while(1){
		distance = read_ultrasonic();
		//sdistance = distance/58; 
		if (distance < 30){
			PORTA = 0x01; 
		}
		else if ( distance >= 30 && distance < 60) {
			PORTA = 0x02; 
		}
		else if (distance >= 60 && distance < 90){
			PORTA = 0x04;
		}
		else if (distance >= 90 && distance < 120){
			PORTA = 0x08;		
		}
		else {
			PORTA = 0x02; 
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}
}

int read_ultrasonic(){
	int count = 0;
	PORTB = 0x00;		// Ping all ultrasonic for 10 us
	_delay_us(10);		     //
	PORTB = 0xFF;		// Set port A to LOW

	_delay_ms(1);		     // delay to wait for transmitter to die off
	for (int i=0;i < 10000;i++){ // Checking port in loop 10,000 times

		if (~PIND&0x40){	     // read PORTF pin 5 for echo pulse
			count++;	// count if still high count
		}
	}

	return count/58;
}
