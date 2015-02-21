/*
 * jdefo002_lab3_part4.c - April 17, 2013
 * Name: Joshua DeForest-Williams E-mail jdefo002@ucr.edu
 * CS Login: Jdefo002
 * Partner Name: Ariana Dejaco  E-mail:adeja001@ucr.edu
 * Lab Section: 022
 * Assignment: Lab#3 Exercise#4
 * Exercise Description:A household has a digital combination deadbolt
 * lock system on the doorway. The system has buttons on a keypad. Button
 * 'X' connects to PA0, 'Y' to PA1, and '#' to PA2. Pressing and
 * releasing '#', then pressing 'Y', should unlock the door by setting
 * PB0 to 1. Any other sequence fails to unlock. Pressing a button from
 * inside the house (PA7) locks the door (PB0=0). For debugging purposes,
 * give each state a number, and always write the current state to PORTC
 * (consider using the enum state variable). Also, be sure to check that
 * only one button is pressed at a time.
 * (Challenge) Extend the above door so that it can also be locked by entering the earlier code. 
*/
#include <avr/io.h>
#include <avr/sfr_defs.h>
// Current Port Definitions
#define INPUT_DDR		DDRA
#define INPUT_INPORT		PINA
#define INPUT_OUTPORT		PORTA
#define DOOR_DDR     		DDRB
#define DOOR_INPORT		PINB
#define DOOR_OUTPORT		PORTB
#define DEBUG_DDR		DDRC
#define DEBUG_INPORT		PINC
#define DEBUG_OUTPORT		PORTC
// Additional macros not defines in sfr_defs.h
#define SET_PORT_BIT(OUTPORT, BIT)		OUTPORT |= (1 << BIT)
#define CLEAR_PORT_BIT(OUTPORT, BIT)	OUTPORT &= ~(1 << BIT)
unsigned char GetBit(unsigned char x_bit, unsigned char k) {
   return ((x_bit & (0x01 << k)) != 0);
}
char state_num= 0; 
char x; 
char y;
char pound; 
char lock;
char flag = 0; 
char locked_flag = 0; // locked = 0, unlocked = 1; 
enum Door_States{Initial,button_p, button_Pound_wait, wait_y, Release, button_Y, button_lock, 
		locked_y_wait, locked_y} Door_State;
void TickFct_DOOR(){
   switch (Door_State){ // Transitions
      case Initial: // state 0
		if ((x&&y)||(x&&pound)||(x&&lock)||(y&&pound)||(y&&lock)||(pound&&lock) ){
			Door_State = Release; 
		}
		else if (pound&&!y)
		{
			Door_State = button_p;
		}
		else if (lock){
			Door_State = button_lock;
		}		
        break;
	  case button_p: // state 1
		if (!pound && y) {
			Door_State = button_Y;
		}
		else if (!pound && !y) {
			Door_State = wait_y;
		} 

		else
		{
			Door_State = button_Pound_wait;
		}			
		
		break;
      case button_Pound_wait:  // state 2
		if ((x&&y)||(x&&pound)||(x&&lock)||(y&&pound)||(y&&lock)||(pound&&lock) ){
			Door_State = Release;
		}
		else if (pound && flag && locked_flag)
		{
			Door_State = locked_y_wait; 
		}			
		else if (pound && flag && !locked_flag)
		{
			Door_State = button_Pound_wait;
		}
		else if (!pound && y) {
			Door_State = button_Y;
		}
		else if (!pound && !y) {
			Door_State = wait_y;
		}
        break;
	  case wait_y: // state 3
		if ((pound && !y) || (pound && y))
		{
			Door_State = Initial;
		}
		else if (!pound && !y)
		{
			Door_State = wait_y;
		}
		else if (!pound && y)
		{
			Door_State = button_Y;
		}
      case Release: // state 4
		if ((x&&y)||(x&&pound)||(x&&lock)||(y&&pound)||(y&&lock)||(pound&&lock) ){
			Door_State = Release; 
		}
		else 
		{
			Door_State = Initial; 
		}
         break;
      case button_Y:// state 5
		 Door_State = Initial;
         break;
      case button_lock:// state 6
         break;
	  case locked_y_wait: // state 7 
		 if ((pound && !y) || (pound && y))
		{
			Door_State = Initial;
		}
		else if (!pound && !y)
		{
			Door_State = locked_y_wait;
		}
		else if (!pound && y)
		{
			Door_State = locked_y;
		}
		 break; 
	  case locked_y:
		 break; 
	  default:
		
         break;

   }

   switch (Door_State){ //State Actions
	   case button_p:
		Door_State = button_Pound_wait;
		flag = 1; 
		state_num = 1; 
		break; 
      case button_Pound_wait:
		 state_num = 2; 
         break;
	  case wait_y:
		 flag = 0;
		 state_num = 3; 
		 break; 
      case Release:
		  state_num = 4; 
         break;
      case button_Y:
		 SET_PORT_BIT(DOOR_OUTPORT, 0);
		 flag = 0; 
		 state_num = 5; 
		 locked_flag = 1; 
         break;
      case button_lock:
		 CLEAR_PORT_BIT(DOOR_OUTPORT,0);
		 Door_State = Initial;
		 state_num = 6; 
		 locked_flag = 0; 
         break;
	  case locked_y_wait: 
		 state_num = 7; 
		 Door_State = locked_y_wait; 
		 break; 
      case locked_y:
		 state_num = 8; 
		 CLEAR_PORT_BIT(DOOR_OUTPORT, 0); 
		 locked_flag = 0;
		 Door_State = Initial;  
		 break; 
	  default:
		 state_num= 0; 
         break;
         }
   }
//DDRA: Configures each of port A's physical pins to input (0) or output (1)
//PORTA: Writing to this register writes the port's physical pins (Write only)
//PINA: Reading this register reads the values of the port's physical pins (Read only)
int main(void)
{
	DOOR_DDR = 0xFF; //Configures port B's 8 pins as outputs.
	DOOR_OUTPORT = 0x00; //Initialize output on port B to 0x00;
	DEBUG_DDR = 0xFF; //Configures port C's 8 pins as outputs.
	DEBUG_OUTPORT = 0x00; //Initialize output on port C to 0x00;
	INPUT_DDR = 0x00; // Configure Port A's 8 pins as inputs.
	INPUT_OUTPORT = 0xFF; // Configure Port A's 8 pins as inputs.
   Door_State = Initial;
   while(1)
   {
	 x = GetBit(INPUT_INPORT, 0);
	 y = GetBit(INPUT_INPORT, 1);
	 pound = GetBit(INPUT_INPORT, 2);
	 lock = GetBit(INPUT_INPORT, 7);
     TickFct_DOOR ();
     DEBUG_OUTPORT = state_num;
   }
}