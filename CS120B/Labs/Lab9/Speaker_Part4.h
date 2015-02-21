/*
 * Speaker_Part4.h
 *
 * Created: 5/13/2013 1:19:05 PM
 *  Author: Ariana DeJaco
 */ 


#ifndef SPEAKER_PART4_H_
#define SPEAKER_PART4_H_

#define DEBOUNCE_COUNT_LIMIT 200

// The following states are for the speaker
enum	Speaker_States {SpeakerOff, SpeakerOn, SpeakerOnWaitForRelease, SpeakerOffWaitForRelease} SpeakerState;
double  SpeakerFrequency;
unsigned char   DebounceCounter;
int     ToneTimer;

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
	if ((SpeakerState == SpeakerOn) || (SpeakerState == SpeakerOnWaitForRelease))
	{
		// Select the frequency based on the button pressed
		if ((Button2State == ButtonOn) && (Button3State == ButtonOff))
		{
			SpeakerFrequency += 0.001;
		}		
		else if ((Button2State == ButtonOff) && (Button3State == ButtonOn))
		{
			SpeakerFrequency -= 0.001;
		}
		else
			SpeakerFrequency = SpeakerFrequency; // Don't change the frequency....
			
		// Drive the speaker with this frequency
		set_PWM(SpeakerFrequency);
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
	DebounceCounter  = 0;
	SpeakerFrequency = 349.23;
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
			{
				SpeakerState = SpeakerOnWaitForRelease;
				DebounceCounter = 0;
			}
			break;
		
		case SpeakerOn:
			if (Button1State == ButtonOn)
			{
				SpeakerState = SpeakerOffWaitForRelease;
				DebounceCounter = 0;
			}
			break;

		case SpeakerOffWaitForRelease:
			if (DebounceCounter < DEBOUNCE_COUNT_LIMIT)
				DebounceCounter++;  // Wait until we hit DEBOUNCE_COUNT_LIMIT
			else
			{
				if (Button1State == ButtonOff)	
				{
					SpeakerState = SpeakerOff;
				}
				else
					DebounceCounter = 0;	// Wait some more...
			}
			break;
			
		case SpeakerOnWaitForRelease:
			if (DebounceCounter < DEBOUNCE_COUNT_LIMIT)
				DebounceCounter++;  // Wait until we hit DEBOUNCE_COUNT_LIMIT
			else
			{
				if (Button1State == ButtonOff)
				{
					SpeakerState = SpeakerOn;
				}
				else
					DebounceCounter = 0;	// Wait some more....
			}
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

#endif /* SPEAKER_PART4_H_ */