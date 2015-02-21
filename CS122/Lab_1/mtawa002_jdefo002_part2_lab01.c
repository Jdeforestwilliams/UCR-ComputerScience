/* Partner Name & E-mail: Marcel Tawamba mtawa002@ucr.edu

 * Partner Name & E-mail: Joshua DeForest-Williams jdefo002@ucr.edu

 * Lab Section: 022

 * Assignment: Lab # 1 Exercise # 2

 * Exercise Description: Using at least three "concurrent" synchSMs, devise a system where A7A6 being 00 

	executes the above Bouncing LED synchSM, 01 the Pattern Sequencer, and 10 the Music 

	Accompaniment. 11 simply outputs 11111111. While the synchSMs are concurrent, note that all 

	but one will be waiting in a wait state at any time.

 * I acknowledge all content contained herein, excluding template or example

 * code, is my own original work.

 */

#include "rims.h"

/*This code will be shared between state machines.*/
unsigned char TimerFlag = 0;
void TimerISR() {
   TimerFlag = 1;
}


enum SM1_States { SM1_wait_music, SM1_light_show } SM1_State;

TickFct_State_machine_1() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
static unsigned char music [] = {0x00, 0xFF, 0xF0, 0x0F, 0xAA, 0x0A, 0xA0, 0x88, 0x77, 0xBB, 0x44, 0xDD, 0x22, 0xEE, 0x11, 0x00, 0xCC, 0x33, 0xF0, 0xFF};
static unsigned char counter;
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_wait_music;
         break;
      case SM1_wait_music:
         if (!A7 || A6) {
            SM1_State = SM1_wait_music;
         }
         else if (A7 && !A6) {
            SM1_State = SM1_light_show;
            counter = 0;
         }
         break;
      case SM1_light_show:
         if (A7 && !A6) {
            SM1_State = SM1_light_show;
         }
         else if (!A7 || A6) {
            SM1_State = SM1_wait_music;
            B = 0x00;
         }
         break;
      default:
         SM1_State = SM1_wait_music;
      } // Transitions

   switch(SM1_State) { // State actions
      case SM1_wait_music:
         break;
      case SM1_light_show:
         if(counter == 20){
            counter = 0;
         }
         B = music[counter];
         counter++;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum SM2_States { SM2_wait_sequence, SM2_direction_sequence, SM2_forward_sequence, SM2_backward_sequence } SM2_State;

TickFct_State_machine_2() {
   static unsigned char sequence [ ] = {0xFF, 0xF0, 0x0F, 0xCC, 0x55, 0x50, 0x05, 0xAA, 
0xA0, 0x0A};
static unsigned char index;
   switch(SM2_State) { // Transitions
      case -1:
         SM2_State = SM2_wait_sequence;
         break;
      case SM2_wait_sequence:
         if (A7 || !A6) {
            SM2_State = SM2_wait_sequence;
         }
         else if (!A7 && A6) {
            SM2_State = SM2_direction_sequence;
         }
         break;
      case SM2_direction_sequence:
         if (A7 || !A6) {
            SM2_State = SM2_wait_sequence;
            B = 0x00;
         }
         else if (!A0 && (!A7 && A6)) {
            SM2_State = SM2_forward_sequence;
            index = 0;
         }
         else if (A0 && (!A7 && A6)) {
            SM2_State = SM2_backward_sequence;
            index = 10;
         }
         break;
      case SM2_forward_sequence:
         if ((index < 10) && !A0 && (!A7 && A6)) {
            SM2_State = SM2_forward_sequence;
         }
         else if (A7 || !A6) {
            SM2_State = SM2_wait_sequence;
            B = 0x00;
         }
         else if (!(index < 10) && !A0 && (!A7 && A6)) {
            SM2_State = SM2_direction_sequence;
         }
         else if (A0 && (!A7 && A6)) {
            SM2_State = SM2_backward_sequence;
            index = 10;
         }
         break;
      case SM2_backward_sequence:
         if (!(index > 0) && A0 && (!A7 && A6)) {
            SM2_State = SM2_direction_sequence;
         }
         else if ((index > 0) && A0 && (!A7 && A6)) {
            SM2_State = SM2_backward_sequence;
         }
         else if (!A0 && (!A7 && A6)) {
            SM2_State = SM2_forward_sequence;
            index = 0;
         }
         else if (A7 || !A6) {
            SM2_State = SM2_wait_sequence;
            B = 0x00;
         }
         break;
      default:
         SM2_State = SM2_wait_sequence;
      } // Transitions

   switch(SM2_State) { // State actions
      case SM2_wait_sequence:
         break;
      case SM2_direction_sequence:
         B = 0x00;
         break;
      case SM2_forward_sequence:
         B = sequence[index];
         index++;
         break;
      case SM2_backward_sequence:
         B = sequence[index];
         index--;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum SM3_States { SM3_direction, SM3_backward, SM3_forward, SM3_start_bouncing } SM3_State;

TickFct_State_machine_3() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
static unsigned char count;
static unsigned char pattern_forward;
static unsigned char pattern_backward;
   switch(SM3_State) { // Transitions
      case -1:
         SM3_State = SM3_start_bouncing;
         break;
      case SM3_direction:
         if (!A0 && (!A6 && !A7)) {
            SM3_State = SM3_forward;
         }
         else if (A0 && (!A6 && !A7)) {
            SM3_State = SM3_backward;
         }
         else if (A6 || A7) {
            SM3_State = SM3_start_bouncing;
            B = 0x00;
         }
         break;
      case SM3_backward:
         if (!(count < 8) && A0 && (!A6 && !A7)) {
            SM3_State = SM3_direction;
         }
         else if ((count < 8) && A0 && (!A6 && !A7)) {
            SM3_State = SM3_backward;
         }
         else if (!A0 && (!A6 && !A7)) {
            SM3_State = SM3_forward;
            count = 0;
pattern_forward = 1;
         }
         else if (A6 || A7) {
            SM3_State = SM3_start_bouncing;
            B = 0x00;
         }
         break;
      case SM3_forward:
         if (!(count < 8) && !A0 && (!A6 && !A7)) {
            SM3_State = SM3_direction;
         }
         else if ((count < 8) && !A0 && (!A6 && !A7)) {
            SM3_State = SM3_forward;
         }
         else if (A0 && (!A6 && !A7)) {
            SM3_State = SM3_backward;
            count = 0;
pattern_backward = 128;
         }
         else if (A6 || A7) {
            SM3_State = SM3_start_bouncing;
            B = 0x00;
         }
         break;
      case SM3_start_bouncing:
         if (A6 || A7) {
            SM3_State = SM3_start_bouncing;
         }
         else if (!A6 && !A7) {
            SM3_State = SM3_direction;
         }
         break;
      default:
         SM3_State = SM3_start_bouncing;
      } // Transitions

   switch(SM3_State) { // State actions
      case SM3_direction:
         count = 0;
         pattern_forward = 1;
         pattern_backward = 128;
         break;
      case SM3_backward:
         B = pattern_backward;
         pattern_backward = pattern_backward/2;
         count++;
         break;
      case SM3_forward:
         B = pattern_forward;
         pattern_forward = pattern_forward*2;
         count++;
         break;
      case SM3_start_bouncing:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum SM4_States { SM4_wait, SM4_all_on } SM4_State;

TickFct_State_machine_4() {
   
   switch(SM4_State) { // Transitions
      case -1:
         SM4_State = SM4_wait;
         break;
      case SM4_wait:
         if (!A7 || !A6) {
            SM4_State = SM4_wait;
         }
         else if (A7 && A6) {
            SM4_State = SM4_all_on;
         }
         break;
      case SM4_all_on:
         if (A7 && A6) {
            SM4_State = SM4_all_on;
         }
         else if (!A7 || !A6) {
            SM4_State = SM4_wait;
            B = 0x00;
         }
         break;
      default:
         SM4_State = SM4_wait;
      } // Transitions

   switch(SM4_State) { // State actions
      case SM4_wait:
         break;
      case SM4_all_on:
         B = 0xFF;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}
int main() {
   B = 0; //Init outputs
   TimerSet(1000);
   TimerOn();
   SM1_State = -1;
   SM2_State = -1;
   SM3_State = -1;
   SM4_State = -1;
   while(1) {
      TickFct_State_machine_1();
      TickFct_State_machine_2();
      TickFct_State_machine_3();
      TickFct_State_machine_4();
      while (!TimerFlag);
      TimerFlag = 0;
   }
}