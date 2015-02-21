/* Partner Name & E-mail: Marcel Tawamba mtawa002@ucr.edu

 * Partner Name & E-mail: Joshua DeForest-Williams jdefo002@ucr.edu

 * Lab Section: 022

 * Assignment: Lab # 1 Exercise # 1

 * Exercise Description: Music Accompaniment: Use a smart phone/tablet to play at least 20 seconds of a (clean) song 

	of your choice, create a light show that accompanies the song, following the song in some way.

 * I acknowledge all content contained herein, excluding template or example

 * code, is my own original work.

 */

#include "rims.h"

/*Define user variables and functions for this state machine here.*/
unsigned char music [] = {0x00, 0xFF, 0xF0, 0x0F, 0xAA, 0x0A, 0xA0, 0x88, 0x77, 0xBB, 0x44, 0xDD, 0x22, 0xEE, 0x11, 0x00, 0xCC, 0x33, 0xF0, 0xFF};
unsigned char counter;
unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_wait, SM1_light_show } SM1_State;

TickFct_State_machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_wait;
         break;
         case SM1_wait: 
         if (!A0) {
            SM1_State = SM1_wait;
         }
         else if (A0) {
            SM1_State = SM1_light_show;
            counter = 0;
         }
         break;
      case SM1_light_show: 
         if (A0 && counter<20) {
            SM1_State = SM1_light_show;
         }
         else if (!A0 || !(counter < 20)) {
            SM1_State = SM1_wait;
         }
         break;
      default:
         SM1_State = SM1_wait;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_wait:
         B = 0;
         break;
      case SM1_light_show:
         B = music[counter];
         counter++;
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodState_machine_1 = 1000; // 1000 ms default
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