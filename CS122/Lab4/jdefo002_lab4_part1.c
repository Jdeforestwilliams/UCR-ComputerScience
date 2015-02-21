/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 10/16/2014 13:43:43 PST
*/

#include "rims.h"

unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_intial, SM1_increment, SM1_waiting, SM1_decrement, SM1_Both } SM1_State;

TickFct_State_machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_intial;
         break;
         case SM1_intial: 
         if (1) {
            SM1_State = SM1_waiting;
         }
         break;
      case SM1_increment: 
         if (1) {
            SM1_State = SM1_waiting;
         }
         break;
      case SM1_waiting: 
         if (!A0 && !A1) {
            SM1_State = SM1_waiting;
         }
         else if (A0 && !A1 && (B < 2)) {
            SM1_State = SM1_increment;
         }
         else if (!A0 && A1 && !(B==0)) {
            SM1_State = SM1_decrement;
         }
         else if (A0 && A1) {
            SM1_State = SM1_Both;
         }
         break;
      case SM1_decrement: 
         if (1) {
            SM1_State = SM1_waiting;
         }
         break;
      case SM1_Both: 
         if (1) {
            SM1_State = SM1_waiting;
         }
         break;
      default:
         SM1_State = SM1_intial;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_intial:
         B= 0; 
         
         break;
      case SM1_increment:
         B++; 
         break;
      case SM1_waiting:
         break;
      case SM1_decrement:
         B--; 
         break;
      case SM1_Both:
         B= 0x00; 
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodState_machine_1 = 100;
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