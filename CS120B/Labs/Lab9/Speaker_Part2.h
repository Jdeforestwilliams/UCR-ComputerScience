/*
 * Speaker_Part2.h
 *
 * Created: 5/13/2013 1:03:49 PM
 *  Author: Ariana DeJaco
 */

#ifndef SPEAKER_PART2_H_
#define SPEAKER_PART2_H_

// The following states are for the speaker
enum	Speaker_States {SpeakerOff, SpeakerOn} SpeakerState;

/************************************************************************/
/* This function will drive the speaker if the Speaker toggle value     */
/* is 0 then D7 is zero otherwise D7 is driven high.                    */
/************************************************************************/
void DriveSpeaker()
{
	unsigned char SpeakerToggleValue;
	if (SpeakerState == SpeakerOn)
	{
		if (Button1State == ButtonOn)
			SpeakerToggleValue = Button1ToggleValue;
		else if (Button2State == ButtonOn)
			SpeakerToggleValue = Button2ToggleValue;
		else
			SpeakerToggleValue = Button3ToggleValue;

		if (SpeakerToggleValue == 0)
			PORTD &= 0x7F;			// Turn OFF D7
		else
			PORTD |= 0x80;			// Turn ON D7
	}
	else
	{
		PORTD &= 0x7F;			    // Turn OFF D7
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void InitSpeaker()
{
	SpeakerState = SpeakerOff;
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
			if (((Button1State == ButtonOn)  && (Button2State == ButtonOff) && (Button3State == ButtonOff)) ||
				((Button1State == ButtonOff) && (Button2State == ButtonOn)  && (Button3State == ButtonOff)) ||
				((Button1State == ButtonOff) && (Button2State == ButtonOff) && (Button3State == ButtonOn)))
				SpeakerState = SpeakerOn;
			break;

		case SpeakerOn:
			if (! (((Button1State == ButtonOn)  && (Button2State == ButtonOff) && (Button3State == ButtonOff)) ||
				   ((Button1State == ButtonOff) && (Button2State == ButtonOn)  && (Button3State == ButtonOff)) ||
				   ((Button1State == ButtonOff) && (Button2State == ButtonOff) && (Button3State == ButtonOn))))
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

#endif /* SPEAKER_PART2_H_ */