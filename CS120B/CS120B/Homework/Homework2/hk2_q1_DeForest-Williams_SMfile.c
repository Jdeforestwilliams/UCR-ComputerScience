/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.5 --- 4/30/2013 18:56:56 PST
*/

#include "rims.h"

/*Define User Variables and Functions For this State Machine Here.*/

enum Door_States { Door_NONAME, Door_DC, Door_Wait } Door_State;

TickFct_Door_Counter() {
   switch(Door_State) { // Transitions
      case -1:
         Door_State = Door_DC;
         break;
         case Door_DC:
         if (!(A0) 

/* If Door closed Wait.  */) {
            Door_State = Door_DC;
         }
         else if (A0
/*When Door Open*/) {
            Door_State = Door_Wait;
            B++; 
            // Increment B
         }
         break;
      case Door_Wait:
         if (A0
) {
            Door_State = Door_Wait;
         }
         else if (!A0
/*When A0 is ) return.*/) {
            Door_State = Door_DC;
         }
         break;
      default:
         Door_State = Door_DC;
   } // Transitions

   switch(Door_State) { // State actions
      case Door_DC:
         if (A1)
         {
              B = 0; 
         } 
         //If Reset Button Pushed, B is cleared. 
         break;
      case Door_Wait:
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   
   Door_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      TickFct_Door_Counter();} // while (1)
} // Main