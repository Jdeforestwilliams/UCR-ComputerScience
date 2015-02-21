/*
 * jdefo002_lab8_part1.c - April 8, 2013
 * Name: Joshua DeForest-Williams jdefo002@ucr.edu
 * CS Login: jdefo002
 * Partner Name: Ariana DeJaco  E-mail:adeja001@ucr.edu
 * Lab Section: 022
 * Assignment: Lab#8 Exercise# Part1
 * Exercise Description: Rework the LCD and Keypad code to utilize the task scheduler format (Keypad code may continue to utilize a function call or may be modified into an SM task). 	*	All code from here on out should use the task scheduler.
*/
#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>

//variables
	unsigned short j;
	char word_arrays[16] = {'A','D','G','J','M','P','T','W','B','C','E','F'};
   //char a_array[1] = {'A'};
   //char b_array[1] = {'B'};
   //char c_array[1] = {'C'};
   char keypad_counter = 0;
   unsigned char key_time_counter = 0;
   unsigned char final_keypad_number= 0;
   unsigned char a_zero = 0; 
   unsigned char a_one = 0; 
   unsigned char a_two = 0; 
   

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
   key_time_counter++;
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

// Returns '\0' if no key pressed, else returns char '1', '2', ... '9', 'A', ...
// If multiple keys pressed, returns leftmost-topmost one
// Keypad must be connected to port C
/* Keypad arrangement
        PC4 PC5 PC6 PC7
   col  1   2   3   4
row
PC0 1   1 | 2 | 3 | A
PC1 2   4 | 5 | 6 | B
PC2 3   7 | 8 | 9 | C
PC3 4   * | 0 | # | D
*/



/************************************************************************/
/* Gets the value from the KeyPad                                       */
/************************************************************************/
unsigned char GetKeypadKey()
{

	PORTC = 0xEF; // Enable col 4 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return(1); }//1
	if (GetBit(PINC,1)==0) { return(4); }//4
    if (GetBit(PINC,2)==0) { return(7); }//7
	if (GetBit(PINC,3)==0) { return('*'); }//*

	// Check keys in col 2
	PORTC = 0xDF; // Enable col 5 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return(2); }//2
	if (GetBit(PINC,1)==0) { return(5); }//5
	if (GetBit(PINC,2)==0) { return(8); }//8
	if (GetBit(PINC,3)==0) { return('0'); }//0

	// Check keys in col 3
	PORTC = 0xBF; // Enable col 6 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return(3); }//3
	if (GetBit(PINC,1)==0) { return(6); }//6
	if (GetBit(PINC,2)==0) { return(9); }//9
	if (GetBit(PINC,3)==0) { return('#'); }//#

	// Check keys in col 4
	PORTC = 0x7F;
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('A'); }
	if (GetBit(PINC,1)==0) { return('B'); }
	if (GetBit(PINC,2)==0) { return('C'); }
	if (GetBit(PINC,3)==0) { return('D'); }

	return('*'); // default value

}

/************************************************************************/
/* Perform all of the initialization operations here.                   */
/************************************************************************/

/************************************************************************/
/* Process_KeyPad_Task()                                                */
/* This method will advance the LCD task state machine one state per    */
/* timer tick.                                                          */
/************************************************************************/
unsigned char keypad_number = 0;
unsigned char prev_key_num = 0;
int Process_KeyPad_Task(int state)
{
	a_zero = (PINA & 0x01);
	a_one = (PINA & 0x02);
	a_two = (PINA & 0x04);
	if (!a_zero)
	{
		PORTA = 0x08;
	}
	else if (!a_one)
	{
		PORTA = 0x10;
	}
	else if (!a_two)
	{
		PORTA = 0x20; 
	}
    Keypad_tick();
	// return state
	return -1;
}
enum Keypad_States { Initial, first_set, second_set, third_set } Keypad_State;
void Keypad_tick(){
   switch(Keypad_State){
      case -1:
         Keypad_State = Initial;
         break;
      case Initial:
		 keypad_number = GetKeypadKey ();
         if (keypad_number == '*')
            {
               Keypad_State = Initial ;
             }
         else if(!a_zero){
				Keypad_State = first_set;
         }
		 else if (!a_one){
				Keypad_State = second_set;
		 }
		 else if (!a_two)
		 {
			 Keypad_State = third_set; 
		 }
		 else {
			Keypad_State = Initial; 
		 }
         break;
     /* case One_press:
         if ((keypad_number == prev_key_num) && a_zero)
         {
            Keypad_State = Two_press;
            keypad_counter++;
         }
         else {
            Keypad_State = Decipher;
            key_time_counter = 0;
         }
         break;
      case Two_press:
         if ((keypad_number != prev_key_num) && key_time_counter <= 200)
            {
               Keypad_State = Two_press;
            }
         else if ((keypad_number == prev_key_num) && key_time_counter <= 200)
            {
               Keypad_State = Three_press;
               keypad_counter++;
            }
         else {
            Keypad_State = Decipher;
            key_time_counter = 0;
         }
         break;
      case Three_press:
         Keypad_State = Decipher;
         key_time_counter = 0;
         break;*/
     case first_set:
		Keypad_State = Initial; 
         break;
      case second_set:
			Keypad_State = Initial;
			break;
	  case third_set:
			Keypad_State = Initial;
			break;
	  default:
         break;
   }
   switch(Keypad_State){
      case Initial:
         break;
     /* case One_press:
         break;
      case Two_press:
         break;
      case Three_press:
         break;*/
	  case second_set: 
			if (keypad_number == 2){
				final_keypad_number = 'B';
			}
			else if (keypad_number == 3){
				final_keypad_number = 'E';
			}
			else if (keypad_number == 4){
				final_keypad_number = 'H';
			}
			else if (keypad_number == 5){
				final_keypad_number = 'K';
			}
			else if (keypad_number == 6){
				final_keypad_number = 'N';
			}
			else if (keypad_number == 7){
				final_keypad_number = 'R';
			}
			else if (keypad_number == 8){
				final_keypad_number = 'U';
			}
			else if (keypad_number == 9){
				final_keypad_number = 'X';
			}
			break; 
	case third_set:
			if (keypad_number == 2){
				final_keypad_number = 'C';
			}
			else if (keypad_number == 3){
				final_keypad_number = 'F';
			}
			else if (keypad_number == 4){
				final_keypad_number = 'I';
			}
			else if (keypad_number == 5){
				final_keypad_number = 'L';
			}
			else if (keypad_number == 6){
				final_keypad_number = 'O';
			}
			else if (keypad_number == 7){
				final_keypad_number = 'S';
			}
			else if (keypad_number == 8){
				final_keypad_number = 'V';
			}
			else if (keypad_number == 9){
				final_keypad_number = 'Y';
			}
		break;
	case first_set:
			if (keypad_number == 2){
				final_keypad_number = 'A';
			}
			else if (keypad_number == 3){
				final_keypad_number = 'D';
			}
			else if (keypad_number == 4){
				final_keypad_number = 'G';
			}
			else if (keypad_number == 5){
				final_keypad_number = 'J';
			}
			else if (keypad_number == 6){
				final_keypad_number = 'M';
			}
			else if (keypad_number == 7){
				final_keypad_number = 'P';
			}
			else if (keypad_number == 8){
				final_keypad_number = 'T';
			}
			else if (keypad_number == 9){
				final_keypad_number = 'W';
			}
		
		break;
      default:
         break;
	
   }
	
   }


//********* LCD interface synchSM *********************************************

// Define LCD port assignments here so easier to change than if hardcoded below
unsigned char *LCD_Data = &PORTD;	// LCD 8-bit data bus
unsigned char *LCD_Ctrl = &PORTB;	// LCD needs 2-bits for control, use port B
const unsigned char LCD_RS = 3;		// LCD Reset pin is PB3
const unsigned char LCD_E = 4;		// LCD Enable pin is PB4

unsigned char LCD_rdy_g = 0; // Set by LCD interface synchSM, ready to display new string
unsigned char LCD_go_g = 0; // Set by user synchSM wishing to display string in LCD_string_g
unsigned char LCD_string_g[17]; // Filled by user synchSM, 16 chars plus end-of-string char

void LCD_WriteCmdStart(unsigned char cmd) {
	*LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_RS, 0);
	*LCD_Data = cmd;
	*LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_E, 1);
}
void LCD_WriteCmdEnd() {
	*LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_E, 0);
}
void LCD_WriteDataStart(unsigned char Data) {
	*LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_RS,1);
	*LCD_Data = Data;
	*LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_E, 1);
}
void LCD_WriteDataEnd() {
	*LCD_Ctrl = SetBit(*LCD_Ctrl,LCD_E, 0);
}
void LCD_Cursor(unsigned char column ) {
	if ( column < 8 ) {
      // IEEE change this value to 16
		LCD_WriteCmdStart(0x80+column);
	}
	else {
		LCD_WriteCmdStart(0xB8+column); // IEEE change this value to 0xBF+column
	}
}

enum LI_States { LI_Init1, LI_Init2, LI_Init3, LI_Init4, LI_Init5, LI_Init6,
	LI_WaitDisplayString, LI_Clr, LI_PositionCursor, LI_DisplayChar, LI_WaitGo0 } LI_State;

void LI_Tick() {
	static unsigned char i;
	switch(LI_State) { // Transitions
		case -1:
			LI_State = LI_Init1;
			break;
		case LI_Init1:
			LI_State = LI_Init2;
			i=0;
			break;
		case LI_Init2:
			if (i<10) {
				 // Wait 100 ms after power up
				LI_State = LI_Init2;
			}
			else {
				LI_State = LI_Init3;
			}
			break;
		case LI_Init3:
			LI_State = LI_Init4;
			LCD_WriteCmdEnd();
			break;
		case LI_Init4:
			LI_State = LI_Init5;
			LCD_WriteCmdEnd();
			break;
		case LI_Init5:
			LI_State = LI_Init6;
			LCD_WriteCmdEnd();
			break;
		case LI_Init6:
			LI_State = LI_WaitDisplayString;
			LCD_WriteCmdEnd();
			break;
		//////////////////////////////////////////////
		case LI_WaitDisplayString:
			if (!LCD_go_g) {
				LI_State = LI_WaitDisplayString;
			}
			else if (LCD_go_g) {
			 LCD_rdy_g = 0;
				LI_State = LI_Clr;
			}
			break;
		case LI_Clr:
			LI_State = LI_PositionCursor;
			LCD_WriteCmdEnd();
			i=0;
			break;
		case LI_PositionCursor:
			LI_State = LI_DisplayChar;
			LCD_WriteCmdEnd();
			break;
		case LI_DisplayChar:
			if (i<16) {
				LI_State = LI_PositionCursor;
				LCD_WriteDataEnd();
			i++;
			}
			else {
				LI_State = LI_WaitGo0;
				LCD_WriteDataEnd();
			}
			break;
		case LI_WaitGo0:
			if (!LCD_go_g) {
				LI_State = LI_WaitDisplayString;
			}
			else if (LCD_go_g) {
				LI_State = LI_WaitGo0;
			}
			break;
		default:
			LI_State = LI_Init1;
		} // Transitions

	switch(LI_State) { // State actions
		case LI_Init1:
		 LCD_rdy_g = 0;
			break;
		case LI_Init2:
			i++; // Waiting after power up
			break;
		case LI_Init3:
			LCD_WriteCmdStart(0x38);
			break;
		case LI_Init4:
			LCD_WriteCmdStart(0x06);
			break;
		case LI_Init5:
			LCD_WriteCmdStart(0x0F);
			break;
		case LI_Init6:
			LCD_WriteCmdStart(0x01); // Clear
			break;
		//////////////////////////////////////////////
		case LI_WaitDisplayString:
			LCD_rdy_g = 1;
			break;
		case LI_Clr:
			LCD_WriteCmdStart(0x01);
			break;
		case LI_PositionCursor:
			LCD_Cursor(i);
			break;
		case LI_DisplayChar:
			LCD_WriteDataStart(LCD_string_g[i]);
			break;
		case LI_WaitGo0:
			break;
		default:
			break;
	} // State actions
}
//--------END LCD interface synchSM------------------------------------------------

// SynchSM for testing the LCD interface -- waits for button press, fills LCD with repeated random num

enum LT_States { LT_s0, LT_WaitLcdRdy, LT_WaitButton, LT_FillAndDispString,
LT_HoldGo1, LT_WaitBtnRelease } LT_State;

void LT_Tick() {
	static unsigned char i, x, c;
	//char easy_words_
	switch(LT_State) { // Transitions
		case -1:
			LT_State = LT_s0;
			break;
		case LT_s0:
			LT_State = LT_WaitLcdRdy;
			break;
		case LT_WaitLcdRdy:
			if (!LCD_rdy_g) {
				LT_State = LT_WaitLcdRdy;
			}
			else if (LCD_rdy_g) {
				LT_State = LT_WaitButton;
			}
			break;
		case LT_WaitButton:
			if (keypad_number == prev_key_num) {
				LT_State = LT_WaitButton;
			}
			else if (!(keypad_number == prev_key_num)) {
            // Button active low
				LT_State = LT_FillAndDispString;
			}
			break;
		case LT_FillAndDispString:
			LT_State = LT_HoldGo1;
			break;
		case LT_HoldGo1:
			LCD_go_g=0;
		 	LT_State = LT_WaitBtnRelease;
			break;
		case LT_WaitBtnRelease:
			if ((keypad_number == prev_key_num)) {
             // Wait for button release
				LT_State = LT_WaitBtnRelease;
			}
			else if (!(keypad_number == prev_key_num)) {
				LT_State = LT_WaitLcdRdy;
			}
			break;
		default:
			LT_State = LT_s0;
		} // Transitions

	switch(LT_State) { // State actions
		case LT_s0:
			LCD_go_g=0;
			strcpy(LCD_string_g, "________________"); // Init, but never seen, shows use of strcpy though
			break;
		case LT_WaitLcdRdy:
			break;
		case LT_WaitButton:
			break;
		case LT_FillAndDispString:
			//x = final_keypad_number;
			for (i=0; i<16 ; i++) {
				// Fill string with c
				if (final_keypad_number == word_arrays[i]){
					//c = (char)(x ); // c is ascii of num x
					LCD_string_g[i] = final_keypad_number;
					keypad_counter++; 
					
				}
            
       }
			LCD_string_g[i] = '\0'; // End-of-string char
			LCD_go_g = 1; // Display string
			break;
		case LT_HoldGo1:
			break;
		case LT_WaitBtnRelease:
			break;
		default:
			break;
	} // State actions
}
void Init_KeyPad_Task()
{
   DDRA = 0xF8; PORTA = 0x00; // PORTB set to output,Except for PA0 and PA2. PA0 is input switch.
   DDRC = 0xF0; PORTC = 0x0F; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
   Keypad_State = -1;
   char i = 0;
   LCD_string_g[0] = '_';
}
/************************************************************************/
/* Perform all of the initialization operations here.                   */
/************************************************************************/
void Init_LCD_Task()
{
	DDRB = 0xFF; // Set port B to output
	DDRD = 0xFF; // Set port D to output
	DDRA = 0xF8; // PA0 is an input
	LI_State = -1;
	LT_State = -1;
}

/************************************************************************/
/* Process_LCD_Task()                                                   */
/* This method will advance the LCD task state machine one state per    */
/* timer tick.                                                          */
/************************************************************************/
int Process_LCD_Task(int state)
{
	LI_Tick();
	LT_Tick();

	// Don't really needed to pass state information to the scheduler
	return 1;
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
 	Init_KeyPad_Task();
	Init_LCD_Task();

	unsigned long int LCD_Tick    = 10;
	unsigned long int KeyPad_Tick = 10;

	// Calculate the GCD of the LCD and KeyPad tasks
	unsigned long int tmpGCD = findGCD(LCD_Tick, KeyPad_Tick);

	//Greatest common divisor for all tasks or smallest time unit for tasks.
	unsigned long int GCD = tmpGCD;

	//Recalculate GCD periods for scheduler
	unsigned long int LCD_period    = LCD_Tick/GCD;
	unsigned long int KeyPad_period = KeyPad_Tick/GCD;

	// Declare an array of tasks
	static task task1, task2;
	task *tasks[] = { &task1, &task2};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

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

	// Set the timer and turn it on
	TimerSet(GCD);
	TimerOn();

	// Run all tasks forever....
	unsigned short i; // Scheduler for-loop iterator
	while(1)
	{
		// Scheduler code
		for ( i = 0; i < 2; i++ )
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

		Process_LCD_Task(1);
		while(!TimerFlag);
		TimerFlag = 0;
	}
}
/************************************************************************/
/* Perform all of the initialization operations here.                   */
/************************************************************************/
/*
void Init_Hangman_Task()
{
	DDRB = 0xFF; // Set port B to output
	DDRD = 0xFF; // Set port D to output
	DDRA = 0x7F; // PA0 is an input
	LI_State = -1;
	LT_State = -1;
}
enum Hangman_states { Noose, Head, Upper_torso, Right_arm, Left_arm, Right_Hand, Left_hand, Middle_Torso, Lower_Torso,
		Right_leg, Left_leg, Right_foot, Left_foot, Lost } Hangman_State;
void Hangman_tick() {
	switch (Hangman_State){
		case Noose:
			if (j){
				Hangman_State = Head;
			}
			else {
				Hangman_State = Noose;
			}
			break;
		case Head:
			if (j){
				Hangman_State = Upper_torso;
			}
			else {
				Hangman_State = Head;
			}
			break;
		case Upper_torso:
			if (j){
				Hangman_State = Right_arm;
			}
			else {
				Hangman_State = Upper_torso;
			}
			break;
		case Right_arm:
			if (j){
				Hangman_State = Left_arm;
			}
			else {
				Hangman_State = Right_arm;
			}
			break;
		case Left_arm:
			if (j){
				Hangman_State = Right_Hand;
			}
			else {
				Hangman_State = Left_arm;
			}
			break;
		case Right_Hand:
			if (j){
				Hangman_State = Left_hand;
			}
			else {
				Hangman_State = Right_Hand;
			}
			break;
		case Left_hand:
			if (j){
				Hangman_State = Middle_Torso;
			}
			else {
				Hangman_State = Left_hand;
			}
			break;
		case Middle_Torso:
			if (j){
				Hangman_State = Lower_Torso;
			}
			else {
				Hangman_State = Middle_Torso;
			}
			break;
		case Lower_Torso:
			if (j){
				Hangman_State = Right_leg;
			}
			else {
				Hangman_State = Lower_Torso;
			}
			break;
		case Right_leg:
			if (j){
				Hangman_State = Left_leg;
			}
			else {
				Hangman_State = Right_leg;
			}
			break;
		case Left_leg:
			if (j){
				Hangman_State = Right_foot;
			}
			else {
				Hangman_State = Left_leg;
			}
			break;
		case Right_foot:
			if (j){
				Hangman_State = Left_foot;
			}
			else {
				Hangman_State = Right_foot;
			}
			break;
		case Left_foot:
			if (j){
				Hangman_State = Lost;
			}
			else {
				Hangman_State = Left_foot;
			}
			break;
		case Lost:
			break;
		default:
			break;
	}
	switch(Hangman_State){
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
				PORTB = 0XE9; //upper torso
			}
			for (int i = 0; i < 1000; i++)
			{
				PORTA = 0X08;
				PORTB = 0xED;//bottom of arms
			}
			for (int i = 0; i < 1000; i++)
			{
				PORTA = 0X08;
				PORTB = 0xF5;//middle torso right hand
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
				PORTB = 0XE9; //upper torso
			}
			for (int i = 0; i < 1000; i++)
			{
				PORTA = 0X08;
				PORTB = 0xF4;//bottom of arms
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
				PORTB = 0XE9; //Upper Torso and Arms
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
				PORTB = 0XE9; //Upper Torso and Arms
			}
			for (int i = 0; i < 1000; i++)
			{
				PORTA = 0X08;
				PORTB = 0xF4;//bottom of arms
			}
			for (int i = 0; i < 1000; i++)
			{
				PORTA = 0X10;
				PORTB = 0xFD;//lower torso
			}
			break;
		case Right_leg:
			if (j  >=50){
				for (int i = 0; i < 1000; i++)
				{
					PORTA = 0X01;
					PORTB = 0X1D;// noose
				}
			}
			if (j  >=100){
				for (int i = 0; i < 1000; i++)
				{
					PORTA = 0X02;
					PORTB = 0XF4;// head
				}
			}
			if (j  >=150){
				for (int i = 0; i < 1000; i++)
				{
					PORTA = 0X04;
					PORTB = 0XE9; //Upper Torso and Arms
				}
			}
			if (j  >=200){
				for (int i = 0; i < 1000; i++)
				{
					PORTA = 0X08;//
					PORTB = 0xFD;//Dmiddle torso
				}
				}if (j  >=250){
				for (int i = 0; i < 1000; i++)
				{
					PORTA = 0X10;
					PORTB = 0xFD;//lower torso
				}}
				if (j  >=300){
					for (int i = 0; i < 1000; i++)
					{
						PORTA = 0X20;
						PORTB = 0xEF; // upper leg
					}}			break;
		case Left_leg:
			if (j  >=50){
				for (int i = 0; i < 1000; i++)
				{
					PORTA = 0X01;
					PORTB = 0X1D;// noose
				}
			}
			if (j  >=100){
				for (int i = 0; i < 1000; i++)
				{
					PORTA = 0X02;
					PORTB = 0XF4;// head
				}
			}
			if (j  >=150){
				for (int i = 0; i < 1000; i++)
				{
					PORTA = 0X04;
					PORTB = 0XE9; //Upper Torso and Arms
				}
			}
			if (j  >=200){
				for (int i = 0; i < 1000; i++)
				{
					PORTA = 0X08;//
					PORTB = 0xFD;//Dmiddle torso
				}
				}if (j  >=250){
				for (int i = 0; i < 1000; i++)
				{
					PORTA = 0X10;
					PORTB = 0xFD;//lower torso
				}}
				if (j  >=300){
					for (int i = 0; i < 1000; i++)
					{
						PORTA = 0X20;
						PORTB = 0xEB; // upper leg
					}}
			break;
		case Right_foot:
			if (j  >=50){
				for (int i = 0; i < 1000; i++)
				{
					PORTA = 0X01;
					PORTB = 0X1D;// noose
				}
			}
			if (j  >=100){
				for (int i = 0; i < 1000; i++)
				{
					PORTA = 0X02;
					PORTB = 0XF4;// head
				}
			}
			if (j  >=150){
				for (int i = 0; i < 1000; i++)
				{
					PORTA = 0X04;
					PORTB = 0XE9; //Upper Torso and Arms
				}
			}
			if (j  >=200){
				for (int i = 0; i < 1000; i++)
				{
					PORTA = 0X08;//
					PORTB = 0xFD;//Dmiddle torso
				}
				}if (j  >=250){
				for (int i = 0; i < 1000; i++)
				{
					PORTA = 0X10;
					PORTB = 0xFD;//lower torso
				}}
				if (j  >=300){
					for (int i = 0; i < 1000; i++)
					{
						PORTA = 0X20;
						PORTB = 0xEB; // upper leg
					}}
					if (j  >=350){
					for (int i = 0; i < 1000; i++)
					{
						PORTA = 0X40;
						PORTB = 0xF7; // lower leg
					}}
					if (j >=400)
					{
						j = 0;
					}
			break;
		case Left_foot:
			if (j  >=50){
				for (int i = 0; i < 1000; i++)
				{
					PORTA = 0X01;
					PORTB = 0X1D;// noose
				}
			}
			if (j  >=100){
				for (int i = 0; i < 1000; i++)
				{
					PORTA = 0X02;
					PORTB = 0XF4;// head
				}
			}
			if (j  >=150){
				for (int i = 0; i < 1000; i++)
				{
					PORTA = 0X04;
					PORTB = 0XE9; //Upper Torso and Arms
				}
			}
			if (j  >=200){
			for (int i = 0; i < 1000; i++)
			{
				PORTA = 0X08;//
				PORTB = 0xFD;//Dmiddle torso
			}
			}if (j  >=250){
			for (int i = 0; i < 1000; i++)
			{
				PORTA = 0X10;
				PORTB = 0xFD;//lower torso
			}}
			if (j  >=300){
			for (int i = 0; i < 1000; i++)
			{
				PORTA = 0X20;
				PORTB = 0xEB; // upper leg
			}}
			if (j  >=350){
			for (int i = 0; i < 1000; i++)
			{
				PORTA = 0X40;
				PORTB = 0xF6; // lower leg
			}}
			if (j >=400)
			{
				j = 0;
			}

			break;
		case Lost:
			break;
		default:
			break;
	}
	}		*/
/*		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X04;
			PORTB = 0XE9; //top of arms
		}
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X08;
			PORTB = 0xF4;//bottom of arms
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
		*/
/*
		for (int i = 0; i < 1000; i++)
		{
			PORTA = 0X40;
			PORTB = 0xF6; // lower leg
		}*/

int main(void)
{
	/*DDRA = 0XFF;
	PORTA = 0x00;
	DDRB = 0xFF;
	PORTB = 0X00;
	DDRC = 0x00;
	PORTC = 0x00;
	Hangman_State = Noose;

	while(1){
			if (PINC == 0 )
			{
				PORTA = 0X20;
				PORTB = 0xEF;
				j++;
			}

		j = (PINA & 0x80);
		j = !j;
		Hangman_tick();
		*/// The Task scheduler does all of the real work
	RunTaskScheduler();
//}

}
