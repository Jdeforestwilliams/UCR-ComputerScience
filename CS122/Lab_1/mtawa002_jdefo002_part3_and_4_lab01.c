/* Partner Name & E-mail: Marcel Tawamba mtawa002@ucr.edu

 * Partner Name & E-mail: Joshua DeForest-Williams jdefo002@ucr.edu

 * Lab Section: 022

 * Assignment: Lab # 1 Exercise # 3

 * Exercise Description: Develop an idea for system with at least two truly concurrent synchSMs. The more interesting

	the behavior, the better. Note that the concurrency need not only relate to output displays, 

	but may also detect certain events/sequences on the inputs. Capture the system in RIBS and 
	
	simulate.

 * Assignment: Lab # 1 Exercise # 4

 * Exercise Description: Write a specification of your above system for a partner to implement. Write your names along

	with each spec, e.g., Creator: Jonny Smith, Implementer: Marry Jones. 

	Demo the implementation of that other system to the system creator and get their approval that 

	the system is correct.

 * I acknowledge all content contained herein, excluding template or example

 * code, is my own original work.

 */

/*
Creator: Marcel Tawamba
Implementer: Joshua DeForest-Williams
Specification: Alarm System
	- light sensor connected to A0
	- motion sensor connected to A1
	- open door/window sensor connected to A2
	- All three triggered, ask for code
	- If wrong code entered, send to emergency state 
*/

#include "rims.h"

/*This code will be shared between state machines.*/
unsigned char global = 0;
 unsigned char count = 0; 
unsigned char TimerFlag = 0;
void TimerISR() {
   TimerFlag = 1;
}


enum SM1_States { SM1_initial, SM1_light_check, SM1_movement_and_door_check, SM1_wait_passcode } SM1_State;

TickFct_State_machine_1() {
   
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_initial;
         break;
      case SM1_initial:
         if (1) {
            SM1_State = SM1_light_check;
         }
         break;
      case SM1_light_check:
         if (!A0) {
            SM1_State = SM1_light_check;
         }
         else if (A0 ) {
            SM1_State = SM1_movement_and_door_check;
         }
         break;
      case SM1_movement_and_door_check:
         if (A1 && A2 && A0) {
            SM1_State = SM1_wait_passcode;
            count = 1; 
         }
         else if (!A0) {
            SM1_State = SM1_light_check;
         }
         else {
            SM1_State = SM1_movement_and_door_check;
         }
         break;
      case SM1_wait_passcode:
         if (count == 1) {
            SM1_State = SM1_wait_passcode;
         }
         else if (!count) {
            SM1_State = SM1_light_check;
         }
         break;
      default:
         SM1_State = SM1_initial;
      } // Transitions

   switch(SM1_State) { // State actions
      case SM1_initial:
         B =0; 
         break;
      case SM1_light_check:
         break;
      case SM1_movement_and_door_check:
         break;
      case SM1_wait_passcode:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum SM2_States { SM2_wait_count, SM2_check_code, SM2_emergency } SM2_State;

TickFct_State_machine_2() {
   static unsigned char sequence [] = {0xF0, 0x0F};
static unsigned char index;
static unsigned char counter;
   switch(SM2_State) { // Transitions
      case -1:
         SM2_State = SM2_wait_count;
         break;
      case SM2_wait_count:
         if (!count) {
            SM2_State = SM2_wait_count;
         }
         else if (count) {
            SM2_State = SM2_check_code;
            counter = 0;
         }
         break;
      case SM2_check_code:
         if (counter < 10 ) {
            SM2_State = SM2_check_code;
         }
         else if (!(counter < 10) && (global == 0)) {
            SM2_State = SM2_emergency;
            index = 0;
         }
         else if (!(counter < 10) && (global == 1)) {
            SM2_State = SM2_wait_count;
            count = 0;
         }
         break;
      case SM2_emergency:
         if (index < 3) {
            SM2_State = SM2_emergency;
         }
         break;
      default:
         SM2_State = SM2_wait_count;
      } // Transitions

   switch(SM2_State) { // State actions
      case SM2_wait_count:
         break;
      case SM2_check_code:
         if( (A & 0xA0) == 0xA0){
            global = 1;
            counter = 10;
         }
         counter++;
         break;
      case SM2_emergency:
         if(index == 2){
           index = 0;
         }
         B = sequence[index%2];
         index++;
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
   while(1) {
      TickFct_State_machine_1();
      TickFct_State_machine_2();
      while (!TimerFlag);
      TimerFlag = 0;
   }
}