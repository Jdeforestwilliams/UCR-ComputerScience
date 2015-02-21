/* Partner Name & E-mail: Marcel Tawamba mtawa002@ucr.edu

 * Partner Name & E-mail: Joshua DeForest-Williams jdefo002@ucr.edu

 * Lab Section: 022

 * Assignment: Lab # 1 Exercise # 1

 * Exercise Description: Pattern Sequencer: Next, create any sequence of 10 output patterns, such as 11111111, 

	01010101, 10101010, ... (ten such patterns). Store them in an array. Each pattern displays for 1 

	second. A0 being 0 goes through the pattern forwards, 1 backwards..

 * I acknowledge all content contained herein, excluding template or example

 * code, is my own original work.

 */


#include "rims.h"

/*Define user variables and functions for this state machine here.*/
unsigned char sequence [ ] = {0xFF, 0xF0, 0x0F, 0xCC, 0x55, 0x50, 0x05, 0xAA, 0xA0, 0x0A};
unsigned char index;
unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_wait, SM1_forward, SM1_backward } SM1_State;

TickFct_State_machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_wait;
         break;
         case SM1_wait: 
         if (!A0) {
            SM1_State = SM1_forward;
            index = 0;
         }
         else if (A0) {
            SM1_State = SM1_backward;
            index = 10;
         }
         break;
      case SM1_forward: 
         if (index < 10 && !A0) {
            SM1_State = SM1_forward;
         }
         else if (!(index < 10) && !A0) {
            SM1_State = SM1_wait;
         }
         else if (A0) {
            SM1_State = SM1_backward;
            index = 10;
         }
         break;
      case SM1_backward: 
         if (!(index > 0) && A0) {
            SM1_State = SM1_wait;
         }
         else if (index > 0 && A0) {
            SM1_State = SM1_backward;
         }
         else if (!A0) {
            SM1_State = SM1_forward;
            index = 0;
         }
         break;
      default:
         SM1_State = SM1_wait;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_wait:
         B = 0x00;
         break;
      case SM1_forward:
         B = sequence[index];
         index++;
         break;
      case SM1_backward:
         B = sequence[index];
         index--;
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodState_machine_1 = 1000; // 1000 ms default
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