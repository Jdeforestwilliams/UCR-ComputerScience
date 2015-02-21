/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.5 --- 4/30/2013 19:5:7 PST
*/

#include "rims.h"

/*Define User Variables and Functions For this State Machine Here.*/
unsigned char i; 

unsigned char Door_Clk;
void TimerISR() {
   Door_Clk = 1;
}

enum Door_States { Door_NONAME, Door_DC, Door_Wait, Door_Alarm, Door_A_Wait } Door_State;

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
            i = 0; 
            //Initialize i; 
         }
         break;
      case Door_Wait:
         if (A0 && (i < 40)
/*Door Open and to count to 20 seconds*/) {
            Door_State = Door_Wait;
         }
         else if (!A0
/*When A0 is ) return.*/) {
            Door_State = Door_DC;
         }
         else if (A0 && !(i < 40)) {
            Door_State = Door_Alarm;
            i = 0; 
         }
         break;
      case Door_Alarm:
         if (A0 && (i < 2)
/*Door Open, i less than 1 sec*/) {
            Door_State = Door_Alarm;
         }
         else if (!A0
/* If door closes return*/) {
            Door_State = Door_DC;
         }
         else if (A0 && !(i < 2)
/* Door Open , more than 1 sec   */) {
            Door_State = Door_A_Wait;
            i = 0; 
            //reset i; 
         }
         break;
      case Door_A_Wait:
         if (A0 && (i < 6)) {
            Door_State = Door_A_Wait;
         }
         else if (A0 && !(i < 6)) {
            Door_State = Door_Alarm;
            i = 0; 
         }
         else if (!A0) {
            Door_State = Door_DC;
         }
         break;
      default:
         Door_State = Door_DC;
   } // Transitions

   switch(Door_State) { // State actions
      case Door_DC:
         B = 0; 
         break;
      case Door_Wait:
         i++; 
         break;
      case Door_Alarm:
         B0 = 1; 
         i ++; 
         break;
      case Door_A_Wait:
         B0 = 0; 
         i++; 
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodDoor_Counter = 500;
   TimerSet(periodDoor_Counter);
   TimerOn();
   
   Door_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      TickFct_Door_Counter();
      while(!Door_Clk);
      Door_Clk = 0;
   } // while (1)
} // Main