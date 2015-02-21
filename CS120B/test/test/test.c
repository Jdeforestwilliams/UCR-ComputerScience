/*
 * jdefo002_lab8_part3.c - April 8, 2013
 * Name: Joshua DeForest-Williams jdefo002@ucr.edu
 * CS Login: jdefo002
 * Partner Name: Ariana DeJaco  E-mail:adeja001@ucr.edu
 * Lab Section: 022
 * Assignment: Lab#8 Exercise#3
 * Exercise Description: Combine the functionality of the keypad and LCD so when keypad is pressed and released, the character of the button pressed is displayed on the LCD, 
 *	and stays displayed until a different button press occurs (May be accomplished with two tasks: LCD interface & modified test harness).
*/
#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>

unsigned char c_zero = 0; 
unsigned char c_one = 0;
unsigned char counter = 0; 

////////////////////////////////////////////////////////////////////////////////
//Functionality - Sets bit on a PORTx
//Parameter: Takes in a uChar for a PORTx, the pin number and the binary value
//Returns: The new value of the PORTx
unsigned char SetBit(unsigned char pin, unsigned char number, unsigned char bin_value)
{
	return (bin_value ? pin | (0x01 << number) : pin & ~(0x01 << number));
}

////////////////////////////////////////////////////////////////////////////////
//Functionality - Gets bit from a PINx
//Parameter: Takes in a uChar for a PINx and the pin number
//Returns: The value of the PINx
unsigned char GetBit(unsigned char port, unsigned char number)
{
	return ( port & (0x01 << number) );
}

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1ms
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M)
{
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void TimerOn()
{
	// AVR timer/counter controller register TCCR0
	TCCR0 	= 0x0B;	// bit3bit6=10: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: prescaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT0 register will count at 125,000 ticks/s

	// AVR output compare register OCR0.
	OCR0 	= 125;	// Timer interrupt will be generated when TCNT0==OCR0
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT0 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register

	TIMSK 	= 0x02; // bit1: OCIE0 -- enables compare match interrupt

	//Initialize avr counter
	TCNT0 = 0;

	// TimerISR will be called every _avr_timer_cntcurr milliseconds
	_avr_timer_cntcurr = _avr_timer_M;

	//Enable global interrupts
	SREG |= 0x80;	// 0x80: 1000000
}

void TimerOff()
{
	TCCR0 	= 0x00; // bit2bit1bit0=000: timer off
}

void TimerISR() {
	TimerFlag = 1;
	counter++; 
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER0_COMP_vect)
{
	// CPU automatically calls when TCNT0 == OCR0 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; 			// Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0)
	{ 	// results in a more efficient compare
		TimerISR(); 				// Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void Process_LED_Task(){
	LED_tick(); 
}
////////////////////////////////////////////////////////////////////////////////
//Functionality - finds the greatest common divisor of two values
//Parameter: Two long int's to find their GCD
//Returns: GCD else 0
unsigned long int findGCD(unsigned long int a, unsigned long int b)
{
	unsigned long int c;
	while(1){
		c = a % b;
	if( c == 0 ) { return b; }
	a = b;
	b = c;
   }
return 0;
}

////////////////////////////////////////////////////////////////////////////////
//Struct for Tasks represent a running process in our simple real-time operating system
typedef struct _task
{
	// Tasks should have members that include: state, period,
	//a measurement of elapsed time, and a function pointer.
	signed 	 char state; 		//Task's current state
	unsigned long period; 		//Task period
	unsigned long elapsedTime; 	//Time elapsed since last task tick
	int (*TickFct)(int); 		//Task tick function
} task;

// Implement scheduler code from PES.
void RunTaskScheduler()
{
	// Initialize the tasks.
 	//Init_KeyPad_Task();
	//Init_LCD_Task();
	 Init_LED_Task(); 
	
	//unsigned long int LCD_Tick    = 10;
	//unsigned long int KeyPad_Tick = 10;
	unsigned long int LED_Tick    = 1000;
	
	// Calculate the GCD of the LCD and KeyPad tasks
	//unsigned long int tmpGCD = findGCD(LCD_Tick, KeyPad_Tick);

	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD =LED_Tick; //tmpGCD; 

	//Recalculate GCD periods for scheduler
	//unsigned long int LCD_period    = LCD_Tick/GCD;
	//unsigned long int KeyPad_period = KeyPad_Tick/GCD;
	unsigned long int LED_period = LED_Tick;///GCD; 

	// Declare an array of tasks
	static task task1;//, task2;
	task *tasks[] = { &task1};//, &task2};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	// Task 1
	task1.state = -1;//Task initial state.
	task1.period = LED_period;//Task Period.
	task1.elapsedTime = LED_period;//Task current elapsed time.
	task1.TickFct = &Process_LED_Task;//Function pointer for the tick.
	/*
	// Task 1
	task1.state = -1;//Task initial state.
	task1.period = LCD_period;//Task Period.
	task1.elapsedTime = LCD_period;//Task current elapsed time.
	task1.TickFct = &Process_LCD_Task;//Function pointer for the tick.

	// Task 2
	task2.state = -1;//Task initial state.
	task2.period = KeyPad_period;//Task Period.
	task2.elapsedTime = KeyPad_period;//Task current elapsed time.
	task2.TickFct = &Process_KeyPad_Task;//Function pointer for the tick.
*/
	// Set the timer and turn it on
	TimerSet(GCD);
	TimerOn();

	// Run all tasks forever....
	unsigned short i; // Scheduler for-loop iterator
	while(1)
	{
		// Scheduler code
		for ( i = 0; i < 1; i++ )
		{
			// Task is ready to tick
			if ( tasks[i]->elapsedTime == tasks[i]->period )
			{
				// Setting next state for task
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				// Reset the elapsed time for next tick.
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}

		//Process_LCD_Task(1);
		while(!TimerFlag);
		
		TimerFlag = 0;
	}
}
/************************************************************************/
/* Perform all of the initialization operations here.                   */
/************************************************************************/
enum LED_states { Noose, Head, Upper_torso, Right_arm, Left_arm, Right_Hand, Left_hand, Middle_Torso, Lower_Torso,
Right_leg, Left_leg, Right_foot, Left_foot, Lost } LED_State;

void Init_LED_Task()
{
	DDRB = 0xFF; // Set port B to output
	DDRC = 0x00; // Set port D to output
	DDRA = 0xFF; // PA0 is an input
	LED_State = -1;
}

void LED_tick() {
	switch (LED_State){
		case -1:
			LED_State = Noose;
			break; 
		case Noose:
			c_zero = PINC & 0x01; 
			if (!c_zero){
				LED_State = Head;
			}
			else {
				LED_State = Noose;
			}
			break;
		case Head:
			c_zero = PINC & 0x01; 
			if (!c_zero){
				LED_State = Upper_torso;
			}
			else {
				LED_State = Head;
			}
			break;
		case Upper_torso:
			c_zero = PINC & 0x01; 
			if (!c_zero){
				LED_State = Right_arm;
			}
			else {
				LED_State = Upper_torso;
			}
			break;
		case Right_arm:
			c_zero = PINC & 0x01; 
			if (!c_zero){
				LED_State = Left_arm;
			}
			else {
				LED_State = Right_arm;
			}
			break;
		case Left_arm:
			c_zero = PINC & 0x01; 
			if (!c_zero){
				LED_State = Right_Hand;
			}
			else {
				LED_State = Left_arm;
			}
			break;
		case Right_Hand:
			c_zero = PINC & 0x01; 
			if (!c_zero){
				LED_State = Left_hand;
			}
			else {
				LED_State = Right_Hand;
			}
			break;
		case Left_hand:
			c_zero = PINC & 0x01; 
			if (!c_zero){
				LED_State = Middle_Torso;
			}
			else {
				LED_State = Left_hand;
			}
			break;
		case Middle_Torso:
			c_zero = PINC & 0x01; 
			if (!c_zero){
				LED_State = Lower_Torso;
			}
			else {
				LED_State = Middle_Torso;
			}
			break;
		case Lower_Torso:
			c_zero = PINC & 0x01; 
			if (!c_zero){
				LED_State = Right_leg;
			}
			else {
				LED_State = Lower_Torso;
			}
			break;
		case Right_leg:
			c_zero = PINC & 0x01; 
			if (!c_zero){
				LED_State = Left_leg;
			}
			else {
				LED_State = Right_leg;
			}
			break;
		case Left_leg:
			c_zero = PINC & 0x01; 
			if (!c_zero){
				LED_State = Right_foot;
			}
			else {
				LED_State = Left_leg;
			}
			break;
		case Right_foot:
			c_zero = PINC & 0x01; 
			if (!c_zero){
				LED_State = Left_foot;
			}
			else {
				LED_State = Right_foot;
			}
			break;
		case Left_foot:
			c_zero = PINC & 0x01; 
			if (!c_zero){
				LED_State = Lost;
			}
			else {
				LED_State = Left_foot;
			}
			break;
		case Lost:
			LED_State = Noose;
			break;
		default:
			break;
	}
	switch(LED_State){
		case Noose:
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X01;
			PORTB = 0X1D;// noose
		}
		break;
		case Head:
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X01;
			PORTB = 0X1D;// noose
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X02;
			PORTB = 0X1D;// head
		}
		break;
		case Upper_torso:
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X01;
			PORTB = 0X1D;// noose
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X02;
			PORTB = 0X1D;// head
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X04;
			PORTB = 0XFD; //upper torso
		}
		break;
		case Right_arm:
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X01;
			PORTB = 0X1D;// noose
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X02;
			PORTB = 0X1D;// head
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X04;
			PORTB = 0XFD; //upper torso
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X04;
			PORTB = 0XED; //top of arms
		}
		break;
		case Left_arm:
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X01;
			PORTB = 0X1D;// noose
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X02;
			PORTB = 0X1D;// head
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X04;
			PORTB = 0XFD; //upper torso
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X04;
			PORTB = 0XE9; //top of arms
		}
		break;
		case Right_Hand:
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X01;
			PORTB = 0X1D;// noose
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X02;
			PORTB = 0X1D;// head
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X04;
			PORTB = 0XFD; //upper torso
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X04;
			PORTB = 0XE9; //top of arms
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X02;
			PORTB = 0xFE;//right hand
		}
		
		break;
		case Left_hand:
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X01;
			PORTB = 0X1D;// noose
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X02;
			PORTB = 0X1D;// head
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X04;
			PORTB = 0XFD; //upper torso
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X04;
			PORTB = 0XE9; //top of arms
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X02;
			PORTB = 0xFE;//right hand
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X02;
			PORTB = 0xF6;//left hand
		}		
		break;
		case Middle_Torso:
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X01;
			PORTB = 0X1D;// noose
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X02;
			PORTB = 0X1D;// head
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X04;
			PORTB = 0XFD; //upper torso
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X04;
			PORTB = 0XE9; //top of arms
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X02;
			PORTB = 0xFE;//right hand
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X02;
			PORTB = 0xF6;//left hand
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X08;
			PORTB = 0xFD;//middle torso
		}
		break;
		case Lower_Torso:
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X01;
			PORTB = 0X1D;// noose
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X02;
			PORTB = 0X1D;// head
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X04;
			PORTB = 0XFD; //upper torso
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X04;
			PORTB = 0XE9; //top of arms
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X02;
			PORTB = 0xFE;//right hand
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X02;
			PORTB = 0xF6;//left hand
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X08;
			PORTB = 0xFD;//middle torso
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X10;
			PORTB = 0xFD;//lower torso
		}
		break;
		case Right_leg:
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X01;
			PORTB = 0X1D;// noose
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X02;
			PORTB = 0XF4;// head
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X04;
			PORTB = 0XE9; //Upper Torso and Arms
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X08;//
			PORTB = 0xFD;//Dmiddle torso
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X10;
			PORTB = 0xFD;//lower torso
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X20;
			PORTB = 0xEF; // upper leg
		}
		break;
		case Left_leg:
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X01;
			PORTB = 0X1D;// noose
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X02;
			PORTB = 0XF4;// head
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X04;
			PORTB = 0XE9; //Upper Torso and Arms
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X08;//
			PORTB = 0xFD;//middle torso
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X10;
			PORTB = 0xFD;//lower torso
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X20;
			PORTB = 0xEB; // upper leg
		}
		break;
		case Right_foot:
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X01;
			PORTB = 0X1D;// noose
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X02;
			PORTB = 0XF4;// head
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X04;
			PORTB = 0XE9; //Upper Torso and Arms
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X08;//
			PORTB = 0xFD;//Dmiddle torso
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X10;
			PORTB = 0xFD;//lower torso
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X20;
			PORTB = 0xEB; // upper leg
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X40;
			PORTB = 0xF7; // lower leg
		}
		break;
		case Left_foot:
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X01;
			PORTB = 0X1D;// noose
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X02;
			PORTB = 0XF4;// head
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X04;
			PORTB = 0XE9; //Upper Torso and Arms
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X08;//
			PORTB = 0xFD;//Dmiddle torso
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X10;
			PORTB = 0xFD;//lower torso
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X20;
			PORTB = 0xEB; // upper leg
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X40;
			PORTB = 0xF6; // lower leg
		}
		break;
		case Lost:
			for (int i = 0; i < 100; i++)
			{
				PORTA = 0X01;
				PORTB = 0X1D;// noose
			}
			for (int i = 0; i < 1000; i++)
			{
				PORTA = 0X02;
				PORTB = 0XF4;// head
			}
			for (int i = 0; i < 1000; i++)
			{
				PORTA = 0X04;
				PORTB = 0XE9; //Upper Torso and Arms
			}
			for (int i = 0; i < 1000; i++)
			{
				PORTA = 0X08;//
				PORTB = 0xFD;//Dmiddle torso
			}
			for (int i = 0; i < 1000; i++)
			{
				PORTA = 0X10;
				PORTB = 0xFD;//lower torso
			}
			for (int i = 0; i < 1000; i++)
			{
				PORTA = 0X20;
				PORTB = 0xEB; // upper leg
			}
			for (int i = 0; i < 1000; i++)
			{
				PORTA = 0X40;
				PORTB = 0xF6; // lower leg
			}		
			break;
		default:
			break;
	}
	}		//*/
/*		for (int i = 0; i < 100; i++)
		{
			PORTA = 0X04;
			PORTB = 0XE9; //top of arms
		}
		for (int i = 0; i < 100; i++)
		{
			PORTA = 0X08;
			PORTB = 0xF4;//bottom of arms
		}
		for (int i = 0; i < 100; i++)
		{
			PORTA = 0X10;
			PORTB = 0xFD;//lower torso
		}
		for (int i = 0; i < 100; i++)
		{
			PORTA = 0X20;
			PORTB = 0xEB; // upper leg
		}
		*/
/*
		for (int i = 0; i < 100; i++)
		{
			PORTA = 0X40;
			PORTB = 0xF6; // lower leg
		}*/

int main(void)
{
	DDRA = 0XFF;
	PORTA = 0x00;
	DDRB = 0xFF;
	PORTB = 0X00;
	DDRC = 0x00;
	PORTC = 0x00;
	c_zero = PINC & 0x01;
	unsigned char c_one = PINC & 0x02;
	LED_State = Noose;
	
		TimerSet(1);
		TimerOn();
		while(1){
			LED_tick();
			while(!TimerFlag);
			TimerFlag =0;
			}
	//		}
	// The Task scheduler does all of the real work		 
	//RunTaskScheduler();
}
