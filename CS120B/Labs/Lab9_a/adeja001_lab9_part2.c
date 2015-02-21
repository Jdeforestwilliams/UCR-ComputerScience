/*    adeja001_lab9_part2.c - 5-13-13
*    Name & E-mail: Ariana Dejaco adeja001@ucr.edu
*    CS Login: adeja001
*    Partner(s) Name & E-mail: Joshua DeForest-Williams jdefo002@ucr.edu
*    Lab Section: 22
*    Assignment: Lab # 9 Exercise # 2
*    Exercise Description: For this part of the lab, create a system that
*    has three button inputs and, depending on which button is pressed,
*    the speaker will output either a middle C, D, or E.
*
*    I acknowledge all content contained herein, excluding template or example
*    code, is my own original work.
*/
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <math.h>
#include "Bit.h"
#include "Buttons.h"
#include "KeyPad.h"
#include "Speaker_Part2.h"
#include "Timer0.h"
#include "Schedular.h"

/************************************************************************/
/* Initialize the ports                                                 */
/************************************************************************/
void InitPorts()
{
	// Make PORTD7 as an output. This is connected to the speaker
	DDRD  = 0x80;
	PORTD = 0x7F;  // Do NOT use pull up resistor on
	// Make PORTC Connected to the KeyPad. PC[3:0] are inputs
	// and PC[7:4] are outputs.
	DDRC  = 0xF0;
	PORTC = 0x0F;
	// Make Port A connected to the buttons. Make them all inputs
	DDRA = 0x00;
}

/************************************************************************/
/* This function calculates the frequency used. The math is:			*/
/* T = 1.0 / frequency - Converts to Period                             */
/* Ticks = T * 10,000 - Converts to Ticks. Timer0 Ticks 10,000 Ticks/sec*/
/* Toggle Rate = Ticks / 2.                                             */
/************************************************************************/
unsigned long calculateFrequencyTick(double frequency)
{
	double Period_F = 1.0 / frequency;						// Period = 1 / Frequency
	double TicksPerSecond_F = Period_F * 10000.0;			// Period * 10,000 ticks/second = Ticks.
	long   TicksPerSecond_L = (long) TicksPerSecond_F;		// Convert to a long from a float
	long   ToggleRate = TicksPerSecond_L / 2;				// It takes two toggle to make 1 period
	return ToggleRate;
}

/************************************************************************/
/* Initialize Task Scheduler                                            */
/************************************************************************/
void RunTaskScheduler()
{
	unsigned long int GCD = 1;

	// Declare the local variables. The following are the ticks that the
	// button and keypads need to run in. Initially they are all zero (disabled)
	// They are added depending on which part of the lab we are running.
	unsigned long int Button1Tick = 0;  // Initially disabled
	unsigned long int Button2Tick = 0;  // Initially disabled
	unsigned long int Button3Tick = 0;  // Initially disabled
	unsigned long int KeypadTick  = 0;  // Initially disabled

	////////////////////////////////////////////////////////////////////////////////
	// Determine the real ticks that we need to run the button and keypad - If any..
	// Based on the lab part that we are running.
	////////////////////////////////////////////////////////////////////////////////
#ifdef SPEAKER_PART1_H_
	Button1Tick = calculateFrequencyTick(Button1Frequency);
#endif
#ifdef SPEAKER_PART2_H_
	Button1Tick = calculateFrequencyTick(Button1Frequency);
	Button2Tick = calculateFrequencyTick(Button2Frequency);
	Button3Tick = calculateFrequencyTick(Button3Frequency);
#endif
#ifdef SPEAKER_PART3_H_
	Button1Tick = 100;   // Good number for button sampling....
#endif
#ifdef SPEAKER_PART4_H_
	Button1Tick = 100;   // Good number for button sampling....
	Button2Tick = 10;    // Sounds good for increasing freq
	Button3Tick = 10;    // Sounds good for decreasing freq
#endif
#ifdef SPEAKER_PARTCHALLANGE_H_
	KeypadTick  = 100;   // Good number for button sampling....
#endif

	//Recalculate GCD periods for scheduler
	unsigned long int SpeakerPeriod = GCD;		// Speaker must be driven at the fastest rate (Twice the fastest button).
	unsigned long int Button1Period = Button1Tick/GCD;
	unsigned long int Button2Period = Button2Tick/GCD;
	unsigned long int Button3Period = Button3Tick/GCD;
	unsigned long int KeyPadPeriod  = KeypadTick/GCD;

	// Declare an array of tasks
	static task task1, task2, task3, task4, task5;
	task *tasks[] = { &task1, &task2, &task3, &task4, &task5};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	// Task 1
	task1.state = (int) SpeakerOff;     //Task initial state.
	task1.period = SpeakerPeriod;       //Task Period.
	task1.elapsedTime = SpeakerPeriod;  //Task current elapsed time.
	task1.TickFct = &SpeakerTask;       //Function pointer for the tick.

	// Task 2
	task2.state = (int) ButtonOff;     //Task initial state.
	task2.period = Button1Period;       //Task Period.
	task2.elapsedTime = Button1Period;  //Task current elapsed time.
	task2.TickFct = &Button1Task;       //Function pointer for the tick.

	// Task 3
	task3.state = (int) ButtonOff;     //Task initial state.
	task3.period = Button2Period;       //Task Period.
	task3.elapsedTime = Button2Period;  //Task current elapsed time.
	task3.TickFct = &Button2Task;       //Function pointer for the tick.

	// Task 4
	task4.state = (int) ButtonOff;     //Task initial state.
	task4.period = Button3Period;       //Task Period.
	task4.elapsedTime = Button3Period;  //Task current elapsed time.
	task4.TickFct = &Button3Task;       //Function pointer for the tick.

	// Task 5
	task5.state = (int) KeyPadOff;      //Task initial state.
	task5.period = KeyPadPeriod;        //Task Period.
	task5.elapsedTime = KeyPadPeriod;   //Task current elapsed time.
	task5.TickFct = &KeyPadTask;        //Function pointer for the tick.

	// Set the timer and turn it on
	TimerSet(GCD);
	TimerOn();

	// Run all tasks forever....
	unsigned short i; // Scheduler for-loop iterator
	while(1)
	{
		// Scheduler code
		for ( i = 0; i < numTasks; i++ )
		{
			if (tasks[i]->period != 0)
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
		}

		// Process_LCD_Task(1);
		while(!TimerFlag);
		TimerFlag = 0;
	}
}

int main(void)
{
   InitPorts();
   InitSpeaker();
   RunTaskScheduler();
}