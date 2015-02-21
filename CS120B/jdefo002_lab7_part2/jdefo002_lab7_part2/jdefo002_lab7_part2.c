/*	jdefo002_lab6_part2.c - 4/29/13
 *	Name: Joshua DeForest-Williams Email: Jdefo002@ucr.edu
 *	CS Login: jdefo002
 *	Partner(s) Name: Ariana Dejaco E-mail: Adeja001@ucr.edu
 *	Lab Section:022
 *	Assignment: Lab #7  Exercise #2
 *	Exercise Description:Connect LEDs to PB0, PB1, PB2, and PB3. Light
 *	the three LEDs PB0, PB1, and PB2 in sequence for 1 second each.
 *	Meanwhile, blink PB3 on 1 second and off 1 second.
 *	EXTENSION: Modify the above example so the three LEDs light for
 *	300 ms, while PB3's LED still blinks 1 second on and 1 second off.
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */



#include <avr/io.h>
#include <avr/interrupt.h>
volatile unsigned char TimerFlag=0; // TimerISR() sets this to 1. C programmer should clear to 0.
// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M=1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr=0; // Current internal count of 1ms ticks
volatile unsigned char B = 0x01;
volatile unsigned char Blink = 0x08;
volatile unsigned char Count_Time = 3;
volatile unsigned char Blink_Time = 10;
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
   Count_Time++;
   Blink_Time++;
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

enum Counter_States { InitState, SecState, ThirdState } CounterState;

unsigned char TckFct_Counter()
{
	// Variable we are returning


	switch(CounterState)
	{
		//Transitions
		case InitState:  // Initial Transition
         B=0x01;
			CounterState = SecState;
         break;
		case SecState:  // Initial Transition
         B=0x02;
			CounterState = ThirdState;
         break;
		case ThirdState:  // Initial Transition
         B=0x04;
			CounterState = InitState;
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
enum Blink_State { InitialState, Blink_two } BlinkState;

unsigned char TckFct_Blink()
{
	// Variable we are returning


	switch(BlinkState)
	{
		//Transitions
		case InitialState:  // Initial Transition
         Blink =0x08;
         BlinkState = Blink_two;
			break;
      case Blink_two:
         Blink = 0x00;
         BlinkState = InitialState;
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
void main()
{
    DDRB = 0xFF; // Set port B to output
    PORTB = 0x00; // Init port B to 0s
    TimerSet(100);
    TimerOn();
    CounterState = InitState;
    BlinkState = InitialState;
    while(1) {
        // User code
        if (Count_Time == 3){
            TckFct_Counter();
            Count_Time = 0;
        }
        if (Blink_Time == 10){
           TckFct_Blink();
           Blink_Time = 0;
        }
        PORTB = B|Blink;
       while (!TimerFlag);    // Wait 1 sec
        TimerFlag = 0;
        // Note: For the above a better style would use a synchSM with TickSM()
        // This example just illustrates the use of the ISR and flag
    }
}