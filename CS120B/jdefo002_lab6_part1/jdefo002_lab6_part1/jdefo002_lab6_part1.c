
#include <avr/io.h>
#include <avr/interrupt.h>
volatile unsigned char TimerFlag=0; // TimerISR() sets this to 1. C programmer should clear to 0.
// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M=1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr=0; // Current internal count of 1ms ticks
void TimerOn() {
	// AVR timer/counter controller register TCCR0
	TCCR0 = 0x0B;    // bit3bit6=10: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT0 register will count at 125,000 ticks/s
	// AVR output compare register OCR0.
	OCR0 = 125;    // Timer interrupt will be generated when TCNT0==OCR0
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT0 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK = 0x02; // bit1: OCIE0 -- enables compare match interrupt
	//Initialize avr counter
	TCNT0=0;
	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds
	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}
void TimerOff() {
	TCCR0 = 0x00; // bit2bit1bit0=000: timer off
}
void TimerISR(){
	TimerFlag = 1;
}
// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER0_COMP_vect)
{
	// CPU automatically calls when TCNT0 == OCR0 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}
volatile unsigned char B = 0x01;
enum Counter_States { InitState } CounterState;
unsigned char TckFct_Counter()
{
	// Variable we are returning
	switch(CounterState)
	{
		//Transitions
		case InitState:  // Initial Transition
		if ( B < 4)
		{
			B = B<<1;
			CounterState = InitState;
		}
		else if (!(B<4))
		{
			B = 0x01;
			CounterState = InitState;
		}
		break;
		default:
		break;
	}
	
	switch(CounterState)
	{ // Actions
		case InitState:
		break;
		default:
		break;
	}
}
int main(void)
{
	DDRB = 0xFF; // Set port B to output
	PORTB = 0x00; // Init port B to 0s
	TimerSet(1000);
	TimerOn();
	while(1) {
		// User code
		TckFct_Counter();
		PORTB = B;
		while (!TimerFlag);    // Wait 1 sec
		TimerFlag = 0;
		// Note: For the above a better style would use a synchSM with TickSM()
		// This example just illustrates the use of the ISR and flag
	}
}