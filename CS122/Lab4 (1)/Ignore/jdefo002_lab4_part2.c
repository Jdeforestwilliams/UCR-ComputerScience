/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 10/16/2014 21:2:4 PST
*/

#include "rims.h"

/*This code will be shared between state machines.*/
unsigned char go = 1; 
typedef struct task {
   int state;
   unsigned long period;
   unsigned long elapsedTime;
   int (*TickFct)(int);
} task;

task tasks[4];

const unsigned char tasksNum = 4;
const unsigned long periodF_Light_1 = 250;
const unsigned long periodF_Light_3 = 250;
const unsigned long periodButton_Press_4 = 1000;
const unsigned long periodF_Light_2 = 250;

const unsigned long tasksPeriodGCD = 250;

int TickFct_F_Light_1(int state);
int TickFct_F_Light_3(int state);
int TickFct_Button_Press_4(int state);
int TickFct_F_Light_2(int state);

unsigned char processingRdyTasks = 0;
void TimerISR() {
   unsigned char i;
   if (processingRdyTasks) {
      printf("Period too short to complete tasks\n");
   }
   processingRdyTasks = 1;
   for (i = 0; i < tasksNum; ++i) { // Heart of scheduler code
      if ( tasks[i].elapsedTime >= tasks[i].period ) { // Ready
         tasks[i].state = tasks[i].TickFct(tasks[i].state);
         tasks[i].elapsedTime = 0;
      }
      tasks[i].elapsedTime += tasksPeriodGCD;
   }
   processingRdyTasks = 0;
}
int main() {
   // Priority assigned to lower position tasks in array
   unsigned char i=0;
   tasks[i].state = -1;
   tasks[i].period = periodF_Light_1;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_F_Light_1;

   ++i;
   tasks[i].state = -1;
   tasks[i].period = periodF_Light_3;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_F_Light_3;

   ++i;
   tasks[i].state = -1;
   tasks[i].period = periodButton_Press_4;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_Button_Press_4;

   ++i;
   tasks[i].state = -1;
   tasks[i].period = periodF_Light_2;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_F_Light_2;

   ++i;
   TimerSet(tasksPeriodGCD);
   TimerOn();
   
   while(1) { Sleep(); }

   return 0;
}

enum FL1_States { FL1_F_Light_1, FL1_F_Light_2, FL1_F_Light_3, FL1_F_Light_4, FL1_Go_L1, FL1_F_Light_0 } FL1_State;
int TickFct_F_Light_1(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
 static unsigned char count = 0; 
   switch(state) { // Transitions
      case -1:
         state = FL1_Go_L1;
         break;
      case FL1_F_Light_1:
         if (go !=0 ) {
            state = FL1_Go_L1;
         }
         else if (go == 0 && count == 0 ) {
            state = FL1_F_Light_2;
         }
         else if (go == 0 && count == 1 ) {
            state = FL1_F_Light_0;
         }
         break;
      case FL1_F_Light_2:
         if (go != 0) {
            state = FL1_Go_L1;
         }
         else if (go == 0 && count == 0 ) {
            state = FL1_F_Light_3;
         }
         else if (go == 0 && count == 1 ) {
            state = FL1_F_Light_1;
         }
         break;
      case FL1_F_Light_3:
         if (go != 0) {
            state = FL1_Go_L1;
         }
         else if (go == 0 && count == 0 ) {
            state = FL1_F_Light_4;
         }
         else if (go == 0 && count == 1 ) {
            state = FL1_F_Light_2;
         }
         break;
      case FL1_F_Light_4:
         if (go != 0) {
            state = FL1_Go_L1;
         }
         else if (go == 0 && count == 1 ) {
            state = FL1_F_Light_3;
         }
         break;
      case FL1_Go_L1:
         if (go != 0 ) {
            state = FL1_Go_L1;
         }
         else if (go == 0) {
            state = FL1_F_Light_0;
         }
         break;
      case FL1_F_Light_0:
         if (go == 0 && count == 0 ) {
            state = FL1_F_Light_1;
         }
         else if (go != 0 ) {
            state = FL1_Go_L1;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case FL1_F_Light_1:
         B = 0x81; 
         break;
      case FL1_F_Light_2:
         B = 0xC3;
         break;
      case FL1_F_Light_3:
         B = 0xE7;
         break;
      case FL1_F_Light_4:
         B = 0xFF; 
         count = 1; 
         break;
      case FL1_Go_L1:
         count = 0; 
         break;
      case FL1_F_Light_0:
         B = 0x00; 
         count = 0; 
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   FL1_State = state;
   return state;
}


enum FL3_States { FL3_Go_L3, FL3_FL3_1 } FL3_State;
int TickFct_F_Light_3(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
static unsigned char FL3_count = 0; 
static unsigned counter =  0; 
   switch(state) { // Transitions
      case -1:
         state = FL3_Go_L3;
         break;
      case FL3_Go_L3:
         if (go != 2) {
            state = FL3_Go_L3;
         }
         else if (go == 2 ) {
            state = FL3_FL3_1;
         }
         break;
      case FL3_FL3_1:
         if (go != 2) {
            state = FL3_Go_L3;
         }
         else if (go == 2) {
            state = FL3_FL3_1;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case FL3_Go_L3:
         FL3_count =0 ; 
         break;
      case FL3_FL3_1:
         if (FL3_count < 16) {
         B = (counter << 4) | counter;
         FL3_count++; 
         counter++; 
         }
         if (!(FL3_count < 16)){
         FL3_count = 0; 
         counter = 0; 
         }
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   FL3_State = state;
   return state;
}


enum Go4_States { Go4_Go_1, Go4_Go_2, Go4_Go_3 } Go4_State;
int TickFct_Button_Press_4(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
   switch(state) { // Transitions
      case -1:
         state = Go4_Go_1;
         break;
      case Go4_Go_1:
         if (go == 0 ) {
            state = Go4_Go_1;
         }
         else if (go == 1) {
            state = Go4_Go_2;
         }
         else if (go == 2) {
            state = Go4_Go_3;
         }
         break;
      case Go4_Go_2:
         if (go == 1) {
            state = Go4_Go_2;
         }
         else if (go == 2) {
            state = Go4_Go_3;
         }
         else if (go == 0) {
            state = Go4_Go_1;
         }
         break;
      case Go4_Go_3:
         if (go == 2) {
            state = Go4_Go_3;
         }
         else if (go == 1) {
            state = Go4_Go_2;
         }
         else if (go == 0) {
            state = Go4_Go_1;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case Go4_Go_1:
         if (A0 && !A1 ){
              go = 1; 
         }
         else if (A1 && !A0){
              go = 2; 
         }
         break;
      case Go4_Go_2:
         if (A0 && !A1 ){
              go = 2; 
         }
         else if (A1 && !A0){
              go = 0; 
         }
         break;
      case Go4_Go_3:
         if (A0 && !A1 ){
              go = 0; 
         }
         else if (A1 && !A0){
              go = 1; 
         }
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   Go4_State = state;
   return state;
}


enum SM5_States { SM5_Go_L2, SM5_FL2_0 } SM5_State;
int TickFct_F_Light_2(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
static unsigned char FL2_count = 0x01; 
static unsigned char flag = 0x00; 
   switch(state) { // Transitions
      case -1:
         state = SM5_Go_L2;
         break;
      case SM5_Go_L2:
         if (go != 1) {
            state = SM5_Go_L2;
         }
         else if (go == 1) {
            state = SM5_FL2_0;
         }
         break;
      case SM5_FL2_0:
         if (go != 1) {
            state = SM5_Go_L2;
         }
         else if (go == 1 && !flag) {
            state = SM5_FL2_0;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM5_Go_L2:
         flag = 0;
         FL2_count = 0; 
         break;
      case SM5_FL2_0:
         if (!flag){
              if (FL2_count < 0x80){
                   FL2_count *= 2; 
                   B = FL2_count; 
              }
              else if (FL2_count > 0x01) {
                   FL2_count /= 2; 
                   B = FL2_count; 
                   flag = 1; 
              }
         }
         else {
              if (FL2_count == 1){
                   flag = 0;
                   FL2_count *= 2;
                   B = FL2_count; 
              }
              else {
                    FL2_count /= 2;
                   B = FL2_count; 
               }
         }
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM5_State = state;
   return state;
}

