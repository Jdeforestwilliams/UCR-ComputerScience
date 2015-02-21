/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.5 --- 4/30/2013 19:18:12 PST
*/

#include "rims.h"

/*Define User Variables and Functions For this State Machine Here.*/
unsigned char i;

unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_NONAME, SM1_Full_Light, SM1_No_Motion, SM1_Dim_Light, SM1_OFF } SM1_State;

TickFct_State_Machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_OFF;
         break;
         case SM1_Full_Light:
         if (A2 && A3) {
            SM1_State = SM1_Full_Light;
         }
         else if (!A2 && A3) {
            SM1_State = SM1_No_Motion;
            i = 0;
         }
         else if (!A3) {
            SM1_State = SM1_OFF;
         }
         break;
      case SM1_No_Motion:
         if ((i < 60) && !A2 && A3) {
            SM1_State = SM1_No_Motion;
         }
         else if (!(i < 60) && !A2 && A3) {
            SM1_State = SM1_Dim_Light;
         }
         else if (A2 && (i < 60) && A3) {
            SM1_State = SM1_Full_Light;
         }
         else if (!A3) {
            SM1_State = SM1_OFF;
         }
         break;
      case SM1_Dim_Light:
         if (A2 && A3) {
            SM1_State = SM1_Full_Light;
         }
         else if (!A2 && A3) {
            SM1_State = SM1_Dim_Light;
         }
         else if (!A3) {
            SM1_State = SM1_OFF;
         }
         break;
      case SM1_OFF:
         if (A3) {
            SM1_State = SM1_Full_Light;
         }
         else if (!A3) {
            SM1_State = SM1_OFF;
         }
         break;
      default:
         SM1_State = SM1_OFF;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_Full_Light:
         B1 = 1;
         B0 = 0;
         break;
      case SM1_No_Motion:
         B1 = 1;
         B0 = 0;
         i++;
         break;
      case SM1_Dim_Light:
         B1 = 0;
         B0 = 1;
         break;
      case SM1_OFF:
         B1 = 0;
         B0 = 0;
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