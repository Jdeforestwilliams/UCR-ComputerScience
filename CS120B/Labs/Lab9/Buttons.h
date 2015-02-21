/*
 * Buttons.h
 *
 * Created: 5/13/2013 7:24:49 AM
 *  Author: Ariana DeJaco
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_

// The following states are for the buttons
enum Button_States {ButtonOff, ButtonOn} Button1State, Button2State, Button3State;
	
// The following toggle values are used to drive the speaker
unsigned char Button1ToggleValue, Button2ToggleValue, Button3ToggleValue;

// Define the frequencies for each button
#define Button1Frequency 261.63
#define Button2Frequency 293.66
#define Button3Frequency 329.63

/************************************************************************/
/* This function represents a Tick on the Button1 state machine.        */
/************************************************************************/
int Button1Task(int currentState)
{
	unsigned char button1Value = GetBit(PINA, 0);
	
	Button1State = (enum Button_States) currentState;

	// State Transitions
	switch (Button1State)
	{
		case ButtonOff:
			if (button1Value == 0)
				Button1State = ButtonOn;
			else
				Button1State = ButtonOff;
			break;
		
		case ButtonOn:
			if (button1Value != 0)
				Button1State = ButtonOff;
			else
				Button1State = ButtonOn;
			break;
		
		// Placed for completeness. This should NEVER happen.
		default:
			Button1State = ButtonOff;
			break;
	}

	// Action Code: When button is pressed toggle button value which will drive the speaker.
	if (Button1State == ButtonOn)
	{
		if (Button1ToggleValue == 1)
			Button1ToggleValue = 0;
		else
			Button1ToggleValue = 1;
	}		
	
	// Return the current state
	return (int) Button1State;
}

/************************************************************************/
/* This function represents a Tick on the Button2 state machine.        */
/************************************************************************/
int Button2Task(int currentState)
{
	unsigned char button2Value = GetBit(PINA, 1);
	
	Button2State = (enum Button_States) currentState;

	// State Transitions
	switch (Button2State)
	{
		case ButtonOff:
			if (button2Value != 0)
				Button2State = ButtonOn;
			else
				Button2State = ButtonOff;
			break;
		
		case ButtonOn:
			if (button2Value == 0)
				Button2State = ButtonOff;
			else
				Button2State = ButtonOn;
			break;
		
		// Placed for completeness. This should NEVER happen.
		default:
			Button2State = ButtonOff;
			break;
	}

	// Action Code: When button is pressed toggle button value which will drive the speaker.
	if (Button2State == ButtonOn)
	{
		if (Button2ToggleValue == 1)
			Button2ToggleValue = 0;
		else
			Button2ToggleValue = 1;
	}
	
	// Return the current state
	return (int) Button2State;
}


/************************************************************************/
/* This function represents a Tick on the Button3 state machine.        */
/************************************************************************/
int Button3Task(int currentState)
{
	unsigned char button3Value = GetBit(PINA, 2);
	
	Button3State = (enum Button_States) currentState;

	// State Transitions
	switch (Button3State)
	{
		case ButtonOff:
			if (button3Value != 0)
				Button3State = ButtonOn;
			else
				Button3State = ButtonOff;
			break;
		
		case ButtonOn:
			if (button3Value == 0)
				Button3State = ButtonOff;
			else
				Button3State = ButtonOn;
			break;
		
		// Placed for completeness. This should NEVER happen.
		default:
			Button3State = ButtonOff;
			break;
	}

	// Action Code: When button is pressed toggle button value which will drive the speaker.
	if (Button3State == ButtonOn)
	{
		if (Button3ToggleValue == 1)
			Button3ToggleValue = 0;
		else
			Button3ToggleValue = 1;
	}
	
	// Return the current state
	return (int) Button3State;
}

#endif /* BUTTONS_H_ */