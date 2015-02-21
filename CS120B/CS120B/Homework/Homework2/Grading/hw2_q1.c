/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.5 --- 4/27/2013 13:10:3 PST
*/

#include "rims.h"

/*Define User Variables and Functions For this State Machine Here.*/

enum SM1_States { SM1_NONAME, SM1_Closed, SM1_Opened, SM1_Holdpoint, SM1_Reset, SM1_Hold } SM1_State;

TickFct_State_Machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_Closed;
         break;
         case SM1_Closed:
         if (A0) {
            SM1_State = SM1_Opened;
         }
         break;
      case SM1_Opened:
         if (1) {
            SM1_State = SM1_Hold;
         }
         break;
      case SM1_Holdpoint:
         if (A1) {
            SM1_State = SM1_Reset;
         }
         else if ( A0) {
            SM1_State = SM1_Opened;
         }
         break;
      case SM1_Reset:
         if (!A1) {
            SM1_State = SM1_Closed;
         }
         break;
      case SM1_Hold:
         if (A0) {
            SM1_State = SM1_Hold;
         }
         else if (!A0) {
            SM1_State = SM1_Holdpoint;
         }
         break;
      default:
         SM1_State = SM1_Closed;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_Closed:
         B = 0;
         break;
      case SM1_Opened:
         B++;
         break;
      case SM1_Holdpoint:
         break;
      case SM1_Reset:
         B=0;
         break;
      case SM1_Hold:
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