/*
 * Speaker_Part3.h
 *
 * Created: 5/13/2013 1:08:28 PM
 *  Author: Ariana DeJaco
 */ 

#ifndef SPEAKER_PART3_H_
#define SPEAKER_PART3_H_

// The following states are for the speaker
enum	Speaker_States {SpeakerOff, SpeakerOn} SpeakerState;

/************************************************************************/
/* This code is for PART 3 of the lab and is used to configures the D7  */
/* to toggle automatically using Timer2 of ATMega32.                    */
/* Timer2 Page 125: WGM21 = 1, WGM20 = 0 is CTC mode.                   */
/*             CTC mode is clear timer on compare match. (page 119)     */
/* Timer2 Page 126: COM21 = 0, COM20 = 1 is Toggle on compare.          */
/* Timer2 Page 127: CS22 = 1, CS21 = 0, CS20 = 0 -> Clk / 64.           */
/************************************************************************/
void InitPWM() 
{
	TCCR2 = (1 << WGM21) | (1 << COM20) | (1 << CS22) ;
}

/************************************************************************/
/* Sets the frequency of the Toggle Pin.                                */
/* The correct equation is on of page 120. If you solve for OCRn you    */
/* get the equation listed below for converting freq to OCR2.           */
/************************************************************************/
void set_PWM (double frequency)
{
	if (frequency < 1)
	OCR2 = 0;
	else
	OCR2 = (unsigned char) ((8000000.0 / (128.0 * frequency)) - 1.0);
}

/************************************************************************/
/* This function will drive the speaker if the Speaker toggle value     */
/* is 0 then D7 is zero otherwise D7 is driven high.                    */
/************************************************************************/
void DriveSpeaker()
{
	if (SpeakerState == SpeakerOn)
	{
		// Select the frequency based on the button pressed
		if (Button1State == ButtonOn)
		{
			set_PWM(Button1Frequency);
		}		
		else
		{
			set_PWM(0.0);
		}		
	}
	else
	{
		set_PWM(0.0);
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void InitSpeaker()
{
	SpeakerState = SpeakerOff;
	InitPWM();
}


/************************************************************************/
/* This function represents a Tick on the Button1 state machine.        */
/************************************************************************/
int SpeakerTask(int currentState)
{
	SpeakerState = (enum Speaker_States) currentState;
	
	// State Transitions
	switch (SpeakerState)
	{
		case SpeakerOff:
			if (Button1State == ButtonOn)
				SpeakerState = SpeakerOn;
			break;
	
		case SpeakerOn:
			if (Button1State == ButtonOff)
				SpeakerState = SpeakerOff;
			break;
		
		// Placed for completeness. This should NEVER happen.
		default:
			SpeakerState = SpeakerOff;
			break;
	}
	
	// Action Code: The action code is to simply drive the speaker
	DriveSpeaker();
	
	// Return the current state
	return (int) SpeakerState;
}

#endif /* SPEAKER_PART3_H_ */