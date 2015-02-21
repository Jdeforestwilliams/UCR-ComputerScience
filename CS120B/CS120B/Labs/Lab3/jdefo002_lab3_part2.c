/*
 * jdefo002_lab3_part2.c - April 12, 2013
 * Name: Joshua DeForest-Williams E-mail jdefo002@ucr.edu
 * CS Login: jdefo002
 * Partner Name: Ariana DeJaco  E-mail:adeja001@ucr.edu
 * Lab Section: 022
 * Assignment: Lab#3 Exercise#2
 * Exercise Description: Buttons are connected to PA0 and PA1.
 * Output for PORTC is initially 0. Pressing PA0 increments PORTC
 * (stopping at 9). Pressing PA1 decrements PORTC (stopping at 0).
 * If both buttons are depressed (even if not initially simultaneously),
 * PORTC resets to 0.
*/


#include <avr/io.h>
#include <avr/sfr_defs.h>


// Current Port Definitions
#define INPUT_DDR		DDRA
#define INPUT_INPORT		PINA
#define INPUT_OUTPORT		PORTA
#define COUNT_DDR		DDRC
#define COUNT_INPORT		PINC
#define COUNT_OUTPORT		PORTC

// Additional macros not defines in sfr_defs.h
#define SET_PORT_BIT(OUTPORT, BIT)		OUTPORT |= (1 << BIT)
#define CLEAR_PORT_BIT(OUTPORT, BIT)	OUTPORT &= ~(1 << BIT)

unsigned char count = 0;
 unsigned char flag = 0;
unsigned char GetBit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);
}

enum COUNT_States{Init, Increment ,Decrement, waiting, both}
      COUNT_State;

void TickFct_CNT(){
   switch (COUNT_State){ // Transitions
      case Init:
         if (GetBit (INPUT_INPORT,0) && count < 9){
            COUNT_State = Increment; //Initial State
         }
         else if (GetBit (INPUT_INPORT,1)&& count > 0)
         {
            COUNT_State= Decrement;
         }
         else
         {
            COUNT_State = Init;
         }
         break;
      case Increment:
         if (GetBit (INPUT_INPORT,0)&& GetBit (INPUT_INPORT,1))
         {
            COUNT_State = both;
         }
		 else if (GetBit(INPUT_INPORT,0) && !flag)
		 {
			 COUNT_State = Increment;
		 }
         else
         {
             COUNT_State = waiting;
         }

         break;
      case Decrement:
         if (GetBit (INPUT_INPORT,0)&& GetBit (INPUT_INPORT,1))
         {
            COUNT_State = both;
         }
		else if (GetBit(INPUT_INPORT,1) && !flag)
		{
			COUNT_State = Decrement; 
		}
         else
         {
            COUNT_State = waiting;
         }

         break;

       case waiting:
         if (GetBit (INPUT_INPORT,0)&& GetBit (INPUT_INPORT,1))
         {
            COUNT_State = both;
         }

         if (GetBit (INPUT_INPORT, 0))
         {
            COUNT_State = waiting;
         }
         else if (GetBit (INPUT_INPORT,1))
         {
            COUNT_State = waiting;
         }
         else if (!GetBit (INPUT_INPORT,0) && !GetBit (INPUT_INPORT,1))
         {
            COUNT_State = Init;
         }
         break;
       case both:
         COUNT_State = both;
         break;
       default:
         COUNT_State =Init;
         break;
   }	
   switch (COUNT_State){ //State Actions
      case Increment:
         count = count +1;
         COUNT_State = waiting;
		 flag = 1; 
         break;
      case Decrement:
         count = count - 1;
         COUNT_State= waiting;
         flag = 1;
         break;
      case waiting:
         COUNT_State = waiting;
		 flag = 0; 
         break;
      case both:
         count = 0;
		 flag = 0; 
         COUNT_State = Init;
         break;
      default:
         break;

   }
   }


//DDRA: Configures each of port A's physical pins to input (0) or output (1)
//PORTA: Writing to this register writes the port's physical pins (Write only)
//PINA: Reading this register reads the values of the port's physical pins (Read only)
int main(void)
{
	COUNT_DDR = 0xFF; //Configures port B's 8 pins as outputs.
	COUNT_OUTPORT = 0x00; //Initialize output on port C to 0x00;
	INPUT_DDR = 0x00; // Configure Port A's 8 pins as inputs.
	INPUT_OUTPORT = 0xFF; // Configure Port A's 8 pins as inputs.
   COUNT_State = Init;
   while(1)
   {
     TickFct_CNT ();
        COUNT_OUTPORT = count;
   }

}
