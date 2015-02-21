/*
 * KeyPad.h
 *
 * Created: 5/13/2013 6:50:46 AM
 *  Author: Ariana DeJaco
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

// The following states are for the buttons
enum KeyPad_States {KeyPadOff, Key1, Key2, Key3, Key4, Key5, Key6, Key7, OtherKey} KeyPadState;
	
#define KEY1_FREQUENCY  261.63
#define KEY2_FREQUENCY  293.66
#define KEY3_FREQUENCY  329.63
#define KEY4_FREQUENCY  349.23
#define KEY5_FREQUENCY  392.00
#define KEY6_FREQUENCY  440.00
#define KEY7_FREQUENCY  493.88

double KeyPadFrequency;

/************************************************************************/
/* Returns '\0' if no key pressed, else returns char '1', '2', ...      */
/* If multiple keys pressed, returns leftmost-topmost one               */
/* Keypad must be connected to port C                                   */
/* Keypad arrangement                                                   */
/*        PC4 PC5 PC6 PC7                                               */
/*   col  1   2   3   4                                                 */
/* row                                                                  */
/* PC0 1   1 | 2 | 3 | A                                                */
/* PC1 2   4 | 5 | 6 | B                                                */
/* PC2 3   7 | 8 | 9 | C                                                */
/* PC3 4   * | 0 | # | D                                                */
/************************************************************************/

unsigned char GetKeypadKey() 
{
	PORTC = 0xEF; // Enable col 4 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('1'); }
	if (GetBit(PINC,1)==0) { return('4'); }
	if (GetBit(PINC,2)==0) { return('7'); }
	if (GetBit(PINC,3)==0) { return('*'); }

	// Check keys in col 2
	PORTC = 0xDF; // Enable col 5 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('2'); }
	if (GetBit(PINC,1)==0) { return('5'); }
	if (GetBit(PINC,2)==0) { return('8'); }
	if (GetBit(PINC,3)==0) { return('0'); }

	// Check keys in col 3
	PORTC = 0xBF; // Enable col 6 with 0, disable others with 1’s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('3'); }
	if (GetBit(PINC,1)==0) { return('6'); }
	if (GetBit(PINC,2)==0) { return('9'); }
	if (GetBit(PINC,3)==0) { return('#'); }

	// Check keys in col 4	
	PORTC = 0x7F;
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('A'); }
	if (GetBit(PINC,1)==0) { return('B'); }
	if (GetBit(PINC,2)==0) { return('C'); }
	if (GetBit(PINC,3)==0) { return('D'); }

	return('\0'); // default value
}

/************************************************************************/
/* This function represents a Tick on the Button1 state machine.        */
/************************************************************************/
int KeyPadTask(int currentState)
{
	// Switching states ONLY depends on the keypad value and not the current state.
	// The state is just the keypad value.
	switch (GetKeypadKey())
	{
		case '\0': KeyPadState = KeyPadOff; break;
		case '1':  KeyPadState = Key1;      break;
		case '2':  KeyPadState = Key2;		break;
		case '3':  KeyPadState = Key3;		break;
		case '4':  KeyPadState = Key4;		break;
		case '5':  KeyPadState = Key5;		break;
		case '6':  KeyPadState = Key6;		break;
		case '7':  KeyPadState = Key7;		break;
		default:   KeyPadState = OtherKey;	break;
	}
	
	// Action Code
	switch (KeyPadState)
	{
		case KeyPadOff: KeyPadFrequency = 0.0;				break;
		case Key1:		KeyPadFrequency = KEY1_FREQUENCY;	break;
		case Key2:		KeyPadFrequency = KEY2_FREQUENCY;	break;
		case Key3:		KeyPadFrequency = KEY3_FREQUENCY;	break;
		case Key4:		KeyPadFrequency = KEY4_FREQUENCY;	break;
		case Key5:		KeyPadFrequency = KEY5_FREQUENCY;	break;
		case Key6:		KeyPadFrequency = KEY6_FREQUENCY;	break;
		case Key7:		KeyPadFrequency = KEY7_FREQUENCY;	break;
		case OtherKey:	KeyPadFrequency = 0.0;				break;
	};		
	
	// Return the current state
	return KeyPadState;
}

#endif /* KEYPAD_H_ */