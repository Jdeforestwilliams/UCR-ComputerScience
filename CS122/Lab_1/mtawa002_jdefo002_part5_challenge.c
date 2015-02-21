/* Partner Name & E-mail: Marcel Tawamba mtawa002@ucr.edu

 * Partner Name & E-mail: Joshua DeForest-Williams jdefo002@ucr.edu

 * Lab Section: 022

 * Assignment: Lab # 1 Exercise # 2

 * Exercise Description: Create a google doc that has a specification and diagrams for future people learning to program 

	state machines . Make it interesting and fun. Perhaps a game or a real application. Show and 

	demo to your TA.s

 * I acknowledge all content contained herein, excluding template or example

 * code, is my own original work.

 */


#include "rims.h"

static unsigned char count = 0; 
unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_Red_Light, SM1_Green_Light, SM1_Yellow_Light, SM1_Off_State } SM1_State;

TickFct_State_machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_Off_State;
         break;
         case SM1_Red_Light: 
         if (A0 && !(count < 10) ) {
            SM1_State = SM1_Green_Light;
            count = 0;
            
         }
         else if ((count <10)) {
            SM1_State = SM1_Red_Light;
         }
         else if (!A0 && !(count < 10)) {
            SM1_State = SM1_Off_State;
            count = 0; 
         }
         break;
      case SM1_Green_Light: 
         if (A0 && !(count < 8)) {
            SM1_State = SM1_Yellow_Light;
            count = 0; 
         }
         else if ((count < 8)) {
            SM1_State = SM1_Green_Light;
         }
         else if (!A0) {
            SM1_State = SM1_Off_State;
            count = 0; 
         }
         break;
      case SM1_Yellow_Light: 
         if ( !(count < 5)) {
            SM1_State = SM1_Red_Light;
            count = 0; 
         }
         else if ((count < 5)) {
            SM1_State = SM1_Yellow_Light;
         }
         else if (!A0) {
            SM1_State = SM1_Off_State;
            count = 0; 
         }
         break;
      case SM1_Off_State: 
         if (!(count < 4)) {
            SM1_State = SM1_Red_Light;
            count = 0; 
         }
         else if ((count < 4)) {
            SM1_State = SM1_Off_State;
         }
         break;
      default:
         SM1_State = SM1_Off_State;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_Red_Light:
         count++; 
         B = 0x01;
         break;
      case SM1_Green_Light:
         count++; 
         B = 0x02;
         break;
      case SM1_Yellow_Light:
         count++;
         B = 0x04;
         break;
      case SM1_Off_State:
         B = 0; 
         count++; 
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodState_machine_1 = 500;
   TimerSet(periodState_machine_1);
   TimerOn();
   
   SM1_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      TickFct_State_machine_1();
      while(!SM1_Clk);
      SM1_Clk = 0;
   } // while (1)
} // Main