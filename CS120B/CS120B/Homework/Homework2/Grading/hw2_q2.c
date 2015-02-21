/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.5 --- 4/30/2013 20:1:45 PST
*/

#include "rims.h"

/*Define User Variables and Functions For this State Machine Here.*/
unsigned char cnt = 0;
unsigned char acnt = 0;

unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_NONAME, SM1_closed, SM1_open, SM1_alarm_on, SM1_alarm_off } SM1_State;

TickFct_State_Machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_closed;
         break;
         case SM1_closed:
         if (A0) {
            SM1_State = SM1_open;
         }
         else if (!A0) {
            SM1_State = SM1_closed;
         }
         break;
      case SM1_open:
         if (!A0) {
            SM1_State = SM1_closed;
         }
         else if (cnt < 20 && A0) {
            SM1_State = SM1_open;
         }
         else if (cnt == 20 && A0) {
            SM1_State = SM1_alarm_on;
         }
         break;
      case SM1_alarm_on:
         if (!A0) {
            SM1_State = SM1_closed;
         }
         else if (A0) {
            SM1_State = SM1_alarm_off;
         }
         break;
      case SM1_alarm_off:
         if (cnt == 3 && A0) {
            SM1_State = SM1_alarm_on;
         }
         else if (cnt < 3 && A0) {
            SM1_State = SM1_alarm_off;
         }
         else if (!A0) {
            SM1_State = SM1_closed;
         }
         break;
      default:
         SM1_State = SM1_closed;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_closed:
         cnt = 0;
         break;
      case SM1_open:
         cnt++;
         break;
      case SM1_alarm_on:
         cnt = 0;
         acnt = 0;
         B0 = 1;
         break;
      case SM1_alarm_off:
         B0 = 0;
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