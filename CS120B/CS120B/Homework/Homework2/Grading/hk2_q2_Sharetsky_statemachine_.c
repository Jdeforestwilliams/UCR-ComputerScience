/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.5 --- 4/30/2013 19:9:39 PST
*/

#include "rims.h"

/*Define user variables for this state machine here.*/
unsigned char i;

unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_NONAME, SM1_Wait, SM1_Door_opened, SM1_Beep, SM1_Dont_beep } SM1_State;

TickFct_State_Machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_Wait;
         break;
         case SM1_Wait:
         if (A0) {
            SM1_State = SM1_Door_opened;
            i = 0;
         }
         else if (!A0) {
            SM1_State = SM1_Wait;
         }
         break;
      case SM1_Door_opened:
         if (!(i > 20) && A0) {
            SM1_State = SM1_Door_opened;
         }
         else if ((i>20) && A0) {
            SM1_State = SM1_Beep;
            i = 0;
         }
         else if (!A0 && !(i > 20)) {
            SM1_State = SM1_Wait;
         }
         break;
      case SM1_Beep:
         if ((i < 1) && A0) {
            SM1_State = SM1_Beep;
         }
         else if (!(i < 1) && A0) {
            SM1_State = SM1_Dont_beep;
            i = 0;
         }
         else if (!A0) {
            SM1_State = SM1_Wait;
         }
         break;
      case SM1_Dont_beep:
         if ((i < 3) && A0) {
            SM1_State = SM1_Dont_beep;
         }
         else if (!(i <3) && A0) {
            SM1_State = SM1_Beep;
            i = 0;
         }
         else if (!A0) {
            SM1_State = SM1_Wait;
         }
         break;
      default:
         SM1_State = SM1_Wait;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_Wait:
         B0 = 0;
         break;
      case SM1_Door_opened:
         i++;
         B0 = 0;
         break;
      case SM1_Beep:
         B0 = 1;
         i++;
         break;
      case SM1_Dont_beep:
         B0 = 0;
         i++;
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