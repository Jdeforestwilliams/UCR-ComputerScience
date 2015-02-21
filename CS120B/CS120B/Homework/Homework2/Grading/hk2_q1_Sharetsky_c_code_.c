/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.5 --- 4/27/2013 11:52:20 PST
*/

#include "rims.h"

/*Define User Variables and Functions For this State Machine Here.*/

enum SM1_States { SM1_NONAME, SM1_Wait, SM1_Door_Opened, SM1_Reset } SM1_State;

TickFct_State_Machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_Wait;
         break;
         case SM1_Wait:
         if (A0 && !A1) {
            SM1_State = SM1_Door_Opened;
            B++;
         }
         else if (A1) {
            SM1_State = SM1_Reset;
         }
         else {
            SM1_State = SM1_Wait;
         }
         break;
      case SM1_Door_Opened:
         if (A0 && !A0) {
            SM1_State = SM1_Door_Opened;
         }
         else if (!A0 && !A0) {
            SM1_State = SM1_Wait;
         }
         else if (A0 && A1) {
            SM1_State = SM1_Reset;
         }
         break;
      case SM1_Reset:
         if (!A1) {
            SM1_State = SM1_Wait;
         }
         break;
      default:
         SM1_State = SM1_Wait;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_Wait:
         break;
      case SM1_Door_Opened:
         break;
      case SM1_Reset:
         B = 0;
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   
   SM1_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      TickFct_State_Machine_1();} // while (1)
} // Main