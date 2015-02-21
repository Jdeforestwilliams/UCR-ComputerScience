/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.5 --- 4/30/2013 20:38:6 PST
*/

#include "rims.h"

/*Define User Variables and Functions For this State Machine Here.*/

unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_NONAME, SM1_s1, SM1_s2, SM1_s3, SM1_s4 } SM1_State;

TickFct_State_Machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_s1;
         break;
         case SM1_s1:
         if (!A0) {
            SM1_State = SM1_s1;
         }
         else if (i=0) {
            SM1_State = SM1_s2;
            A0
         }
         break;
      case SM1_s2:
         if (!A0) {
            SM1_State = SM1_s1;
         }
         else if (A0 && (i < 20)) {
            SM1_State = SM1_s2;
            i++;
         }
         else if (!(i<20)) {
            SM1_State = SM1_s3;
         }
         break;
      case SM1_s3:
         if (1) {
            SM1_State = SM1_s4;
            i=0;
         }
         break;
      case SM1_s4:
         if (!A0 && !(i<3)) {
            SM1_State = SM1_s1;
         }
         else if (A0 && (i < 3)) {
            SM1_State = SM1_s4;
            i++;
         }
         break;
      default:
         SM1_State = SM1_s1;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_s1:
         break;
      case SM1_s2:
         break;
      case SM1_s3:
         B0 = 1;
         break;
      case SM1_s4:
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