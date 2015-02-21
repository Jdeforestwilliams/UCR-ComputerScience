/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.5 --- 5/29/2013 14:34:18 PST
*/

#include "rims.h"


/*This code will be shared between state machines.*/
unsigned char open = 0;
unsigned short closed[]={0,0,0,0,0};
unsigned char TimerFlag = 0;
void TimerISR() {
   TimerFlag = 1;
}


enum SM1_States { SM1_s1, SM1_s2, SM1_s3 } SM1_State;

TickFct_State_Machine_1() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define User Variables and Functions For this State Machine Here.*/
static unsigned char count;
switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_s1;
         break;
         case SM1_s1:
         if (!A0) {
            SM1_State = SM1_s1;
         }
         else if (A0 && open < 3) {
            SM1_State = SM1_s2;
            open++;

         }
         break;
      case SM1_s2:
         if (count < 3 && A0) {
            SM1_State = SM1_s2;
         }
         else if (!(count<3) && A0) {
            SM1_State = SM1_s3;
            count = 0;
         }
         else if (!A0) {
            SM1_State = SM1_s1;
            open--;

         }
         break;
      case SM1_s3:
         if (count < 3 && A0) {
            SM1_State = SM1_s3;
         }
         else if (!A0) {
            SM1_State = SM1_s1;
            open--;
         }
         else if (!(count<3) && A0) {
            SM1_State = SM1_s2;
            count = 0;
         }
         break;
      default:
         SM1_State = SM1_s1;
      } // Transitions

   switch(SM1_State) { // State actions
         case SM1_s1:
         B0 = 0;
count = 0;
         break;
      case SM1_s2:
         B0 = 1;
count++;
         break;
      case SM1_s3:
         B = 0;
count++;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum SM2_States { SM2_s1, SM2_s2, SM2_s3 } SM2_State;

TickFct_State_Machine_2() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here.*/
static unsigned char  count1;
switch(SM2_State) { // Transitions
      case -1:
         SM2_State = SM2_s1;
         break;
         case SM2_s1:
         if (A1 && open < 3) {
            SM2_State = SM2_s2;
            open++;
         }
         else if (!A1) {
            SM2_State = SM2_s1;
         }
         break;
      case SM2_s2:
         if (A1 && !(count1<3)) {
            SM2_State = SM2_s3;
            count1 = 0;
         }
         else if (A1 && count1<3) {
            SM2_State = SM2_s2;
         }
         else if (!A1
) {
            SM2_State = SM2_s1;
            open--;
         }
         break;
      case SM2_s3:
         if (A1 && count1<3) {
            SM2_State = SM2_s3;
         }
         else if (A1 && !(count1<3)) {
            SM2_State = SM2_s2;
            count1 = 0;
         }
         else if (!A1) {
            SM2_State = SM2_s1;
            open--;
         }
         break;
      default:
         SM2_State = SM2_s1;
      } // Transitions

   switch(SM2_State) { // State actions
         case SM2_s1:
         B1 = 0;
count1=0;
         break;
      case SM2_s2:
         B1 = 1;
count1++;
         break;
      case SM2_s3:
         B1 = 0;
count1++;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum SM3_States { SM3_s1, SM3_s2, SM3_s3 } SM3_State;

TickFct_State_Machine_3() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here.*/
static unsigned char count2;
switch(SM3_State) { // Transitions
      case -1:
         SM3_State = SM3_s1;
         break;
         case SM3_s1:
         if (A2 && open < 3) {
            SM3_State = SM3_s2;
            open++;
         }
         else if (!A2) {
            SM3_State = SM3_s1;
         }
         break;
      case SM3_s2:
         if (A2 && !(count2 < 3)) {
            SM3_State = SM3_s3;
            count2 = 0;
         }
         else if (!A2) {
            SM3_State = SM3_s1;
            open--;
         }
         else if (A2 && count2 < 3) {
            SM3_State = SM3_s2;
         }
         break;
      case SM3_s3:
         if (A2 && count2 < 3) {
            SM3_State = SM3_s3;
         }
         else if (A2 && !(count2 < 3)) {
            SM3_State = SM3_s2;
            count2 = 0;
         }
         else if (!A2) {
            SM3_State = SM3_s1;
            open--;
         }
         break;
      default:
         SM3_State = SM3_s1;
      } // Transitions

   switch(SM3_State) { // State actions
         case SM3_s1:
         B2 = 0;
count2 = 0;
         break;
      case SM3_s2:
         B2 = 1;
count2++;
         break;
      case SM3_s3:
         B2 = 0;
count2++;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum SM4_States { SM4_s1, SM4_s2, SM4_s3 } SM4_State;

TickFct_State_Machine_4() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here.*/
static unsigned char count3;
switch(SM4_State) { // Transitions
      case -1:
         SM4_State = SM4_s1;
         break;
         case SM4_s1:
         if (A3 && open < 3) {
            SM4_State = SM4_s2;
            open++;
         }
         else if (!A3) {
            SM4_State = SM4_s1;
         }
         break;
      case SM4_s2:
         if (!A3) {
            SM4_State = SM4_s1;
            open--;
         }
         else if (A3 && count3 < 3) {
            SM4_State = SM4_s2;
         }
         else if (A3 && !(count3 < 3)) {
            SM4_State = SM4_s3;
            count3 = 0;
         }
         break;
      case SM4_s3:
         if (A3 && count3 < 3) {
            SM4_State = SM4_s3;
         }
         else if (A3 && !(count3 < 3)) {
            SM4_State = SM4_s2;
            count3 = 0;
         }
         else if (!A3) {
            SM4_State = SM4_s1;
            open--;
         }
         break;
      default:
         SM4_State = SM4_s1;
      } // Transitions

   switch(SM4_State) { // State actions
         case SM4_s1:
         B3 = 0;
count3 = 0;
         break;
      case SM4_s2:
         B3 = 1;
count3 ++;
         break;
      case SM4_s3:
         B3 = 0;
count3++;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum SM5_States { SM5_s1, SM5_s2, SM5_s3 } SM5_State;

TickFct_State_Machine_5() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here.*/
static unsigned char count4;
switch(SM5_State) { // Transitions
      case -1:
         SM5_State = SM5_s1;
         break;
         case SM5_s1:
         if (A4 && open < 3) {
            SM5_State = SM5_s2;
            open++;
         }
         else if (!A4) {
            SM5_State = SM5_s1;
         }
         break;
      case SM5_s2:
         if (A4 && !(count4 < 3)) {
            SM5_State = SM5_s3;
            count4 = 0;
         }
         else if (A4 && count4 < 3) {
            SM5_State = SM5_s2;
         }
         else if (!A4) {
            SM5_State = SM5_s1;
            open--;
         }
         break;
      case SM5_s3:
         if (A4 && count4 < 3) {
            SM5_State = SM5_s3;
         }
         else if (!A4) {
            SM5_State = SM5_s1;
            open--;
         }
         else if (A4 && !(count4 < 3)) {
            SM5_State = SM5_s2;
            count4 = 0;
         }
         break;
      default:
         SM5_State = SM5_s1;
      } // Transitions

   switch(SM5_State) { // State actions
         case SM5_s1:
         B4 = 0;
count4 = 0;
         break;
      case SM5_s2:
         B4 = 1;
count4++;
         break;
      case SM5_s3:
         B4 = 0;
count4++;
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
   SM5_State = -1;
   while(1) {
      TickFct_State_Machine_1();
      TickFct_State_Machine_2();
      TickFct_State_Machine_3();
      TickFct_State_Machine_4();
      TickFct_State_Machine_5();
      while (!TimerFlag);
      TimerFlag = 0;
   }
}