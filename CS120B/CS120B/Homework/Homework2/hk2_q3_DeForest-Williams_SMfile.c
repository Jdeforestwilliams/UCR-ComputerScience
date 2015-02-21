/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.5 --- 4/27/2013 13:58:35 PST
*/

#include "rims.h"

/*Define User Variables and Functions For this State Machine Here.*/
unsigned char i; 

unsigned char MS_Clk;
void TimerISR() {
   MS_Clk = 1;
}

enum MS_States { MS_NONAME, MS_No_motion, MS_Wait, MS_H_sixty } MS_State;

TickFct_Motion_Sensor() {
   switch(MS_State) { // Transitions
      case -1:
         MS_State = MS_No_motion;
         break;
         case MS_No_motion:
         if (!(A2) 

/* If No Motion Wait.  */) {
            MS_State = MS_No_motion;
         }
         else if (A2
/*When Lights On*/) {
            MS_State = MS_Wait;
            i = 0; 
            //Initialize i; 
            B1 = 1; 
            B0 = 0; 
            //initialize lights. 
         }
         break;
      case MS_Wait:
         if (A2 && (i < 120)
/*Lights and to count to 60 seconds*/) {
            MS_State = MS_Wait;
         }
         else if (!A2 && !(i < 120)) {
            MS_State = MS_No_motion;
         }
         else if (A2 && !(i < 120)) {
            MS_State = MS_H_sixty;
         }
         break;
      case MS_H_sixty:
         if (!A2) {
            MS_State = MS_No_motion;
         }
         break;
      default:
         MS_State = MS_No_motion;
   } // Transitions

   switch(MS_State) { // State actions
      case MS_No_motion:
         B = x01; 
         break;
      case MS_Wait:
         i++; 
         break;
      case MS_H_sixty:
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodMotion_Sensor = 500;
   TimerSet(periodMotion_Sensor);
   TimerOn();
   
   MS_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      TickFct_Motion_Sensor();
      while(!MS_Clk);
      MS_Clk = 0;
   } // while (1)
} // Main