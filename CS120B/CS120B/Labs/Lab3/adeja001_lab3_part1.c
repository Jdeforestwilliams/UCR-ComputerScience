/*
 * adeja001_lab3_part1.c - April 15, 2013
 * Name: Ariana DeJaco  E-mail:adeja001@ucr.edu
 * CS Login: adeja001
 * Partner Name: Joshua DeForest-Williams E-mail jdefo002@ucr.edu
 * Lab Section: 022
 * Assignment: Lab#3 Exercise#1
 * Exercise Description: PB0 and PB1 each connect to an LED, and PB0's
 * LED is initially on. Pressing a button connected to PGetBit (INPUT_INPORT,0) turns off
 * PB0's LED and turns on PB1's LED, staying that way after button release.
 * Pressing the button again turns off PB1's LED and turns on PB0's LED.
*/


#include <avr/io.h>
#include <avr/sfr_defs.h>


// Current Port Definitions
#define INPUT_DDR			DDRA
#define INPUT_INPORT		PINA
#define INPUT_OUTPORT	PORTA
#define LED_DDR			DDRB
#define LED_INPORT		PINB
#define LED_OUTPORT		PORTB

// Additional macros not defines in sfr_defs.h
#define SET_PORT_BIT(OUTPORT, BIT)		OUTPORT |= (1 << BIT)
#define CLEAR_PORT_BIT(OUTPORT, BIT)	OUTPORT &= ~(1 << BIT)

 unsigned char flag = 0;
unsigned char GetBit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);
}
//volatile unsigned char TimerFlag=0; //raised by ISD, lowered by main code.
//void TimerISR() {
  // TimerFlag=1;
//}
enum LED_States{Init, LED0,LED1, reset_flag_led1, reset_flag_led0}
      LED_State;

void TickFct_LED(){
   switch (LED_State){ // Transitions
      case Init:
         LED_State = LED0; //Initial State
         break;
      case LED0:
         if (GetBit (INPUT_INPORT,0) && !flag){ // a=0
            LED_State = LED0;
         }
         else if(!GetBit (INPUT_INPORT,0)){ //a =1
             LED_State = reset_flag_led0;
         }

         break;
      case LED1:

         if (GetBit (INPUT_INPORT,0) && flag) // a=1
         {
            LED_State = LED1;
         }
/*         else if (!flag)
         {
            LED_State= LED0;
         }*/
         else if (!GetBit (INPUT_INPORT,0)) //a =0
         {
            LED_State = reset_flag_led1;
         }

         break;
      case reset_flag_led1:
            if (GetBit (INPUT_INPORT,0))
            {
               LED_State = LED0;
            }
            break;
       case reset_flag_led0:
         if (GetBit (INPUT_INPORT, 0))
         {
            LED_State = LED1;
         }
         break;
        default:
            LED_State =Init;
            break;
   }
   switch (LED_State){ //State Actions
      case LED0:
         SET_PORT_BIT(LED_OUTPORT,0);
         CLEAR_PORT_BIT(LED_OUTPORT,1);
         flag = 0;
         break;
      case LED1:
         SET_PORT_BIT(LED_OUTPORT,1);
         CLEAR_PORT_BIT(LED_OUTPORT,0);
         flag = 1;
         break;
      case reset_flag_led1:
         flag = 0;
         break;
      case reset_flag_led0:
         flag = 1;
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
	LED_DDR = 0xFF; //Configures port B's 8 pins as outputs.
	LED_OUTPORT = 0x00; //Initialize output on port C to 0x00;
	INPUT_DDR = 0x00; // Configure Port A's 8 pins as inputs.
	INPUT_OUTPORT = 0xFF; // Configure Port A's 8 pins as inputs.
   LED_OUTPORT=0;
   //TimerSet(500);
   //TimerOn();
   LED_State = Init;
   while(1)
   {
     TickFct_LED ();
     //while(!TimerFlag) {}
        //TimerFlag = 0;
   }

}
