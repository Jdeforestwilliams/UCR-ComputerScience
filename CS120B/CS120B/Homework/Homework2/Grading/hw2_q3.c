/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.5 --- 4/30/2013 20:13:51 PST
*/

#include "rims.h"

/*Define User Variables and Functions For this State Machine Here.*/
unsigned char cnt = 0;

unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_NONAME, SM1_off, SM1_dim, SM1_on, SM1_delay } SM1_State;

TickFct_State_Machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_off;
         break;
         case SM1_off:
         if (!A2) {
            SM1_State = SM1_off;
         }
         else if (A2) {
            SM1_State = SM1_dim;
         }
         break;
      case SM1_dim:
         if (!A2) {
            SM1_State = SM1_dim;
         }
         else if (A2) {
            SM1_State = SM1_on;
         }
         break;
      case SM1_on:
         if (A2) {
            SM1_State = SM1_on;
         }
         else if (!A2) {
            SM1_State = SM1_delay;
         }
         break;
      case SM1_delay:
         if (cnt < 60 && !A2) {
            SM1_State = SM1_delay;
         }
         else if (A2) {
            SM1_State = SM1_on;
         }
         else if (cnt  > 60 && !A2) {
            SM1_State = SM1_dim;
         }
         break;
      default:
         SM1_State = SM1_off;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_off:
         B1 = 0;
         B0 = 0;
         cnt = 0;
         break;
      case SM1_dim:
         B1 = 0;
         B0 = 1;
         cnt = 0;
         break;
      case SM1_on:
         B1 = 1;
         B0 = 0;
         cnt = 0;
         break;
      case SM1_delay:
         cnt++;
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodState_Machine_1 = 1000; // 1000 ms default
   TimerSet(periodState_Machine_1);
   TimerOn();
   
   SM1_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      TickFct_State_Machine_1();
      while(!SM1_Clk);
      SM1_Clk = 0;
   } // while (1)
} // Main