/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.5 --- 5/29/2013 14:41:3 PST
*/

#include "rims.h"


/*This code will be shared between state machines.*/
unsigned char TimerFlag = 0;
void TimerISR() {
   TimerFlag = 1;
}


enum SM1_States { SM1_Initial, SM1_On, SM1_Off } SM1_State;

TickFct_State_Machine_1() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define User Variables and Functions For this State Machine Here.*/
static unsigned char i;
switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_Initial;
         break;
         case SM1_Initial:
         if (A0) {
            SM1_State = SM1_On;
         }
         else if (!A0) {
            SM1_State = SM1_Initial;
         }
         break;
      case SM1_On:
         if (A0 && i < 3) {
            SM1_State = SM1_On;
         }
         else if (A0 && !(i<3)) {
            SM1_State = SM1_Off;
            i =0;
         }
         else if (!A0) {
            SM1_State = SM1_Initial;
         }
         break;
      case SM1_Off:
         if (A0 && !(i<3)) {
            SM1_State = SM1_On;
            i=0;
         }
         else if ((i<3)) {
            SM1_State = SM1_Off;
         }
         else if (!A0) {
            SM1_State = SM1_Initial;
         }
         break;
      default:
         SM1_State = SM1_Initial;
      } // Transitions

   switch(SM1_State) { // State actions
         case SM1_Initial:
         B0=0;
i=0;

         break;
      case SM1_On:
         i++;
B0=1;
         break;
      case SM1_Off:
         i++;
B0=0;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum SM2_States { SM2_Initial1, SM2_On1, SM2_Off1 } SM2_State;

TickFct_State_Machine_2() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here.*/
static unsigned char j;
switch(SM2_State) { // Transitions
      case -1:
         SM2_State = SM2_Initial1;
         break;
         case SM2_Initial1:
         if (A1) {
            SM2_State = SM2_On1;
         }
         else if (!A1) {
            SM2_State = SM2_Initial1;
         }
         break;
      case SM2_On1:
         if (A1 && !(j< 3)) {
            SM2_State = SM2_Off1;
            j=0;
         }
         else if (A1 && j < 3) {
            SM2_State = SM2_On1;
         }
         else if (!A1) {
            SM2_State = SM2_Initial1;
         }
         break;
      case SM2_Off1:
         if (A1 && j < 3) {
            SM2_State = SM2_Off1;
         }
         else if (A1 && !(j< 3)) {
            SM2_State = SM2_On1;
            j=0;
         }
         else if (!A1) {
            SM2_State = SM2_Initial1;
         }
         break;
      default:
         SM2_State = SM2_Initial1;
      } // Transitions

   switch(SM2_State) { // State actions
         case SM2_Initial1:
         B1=0;
j=0;

         break;
      case SM2_On1:
         j++;
B1=1;
         break;
      case SM2_Off1:
         j++;
B1=0;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum SM3_States { SM3_Initial2, SM3_On2, SM3_Off2 } SM3_State;

TickFct_State_Machine_3() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here.*/
static unsigned char k;
switch(SM3_State) { // Transitions
      case -1:
         SM3_State = SM3_Initial2;
         break;
         case SM3_Initial2:
         if (A2) {
            SM3_State = SM3_On2;
         }
         else if (!A2) {
            SM3_State = SM3_Initial2;
         }
         break;
      case SM3_On2:
         if (A2 && !(k <3)) {
            SM3_State = SM3_Off2;
            k=0;
         }
         else if (A2 && k <3) {
            SM3_State = SM3_On2;
         }
         else if (!A2) {
            SM3_State = SM3_Initial2;
         }
         break;
      case SM3_Off2:
         if (A2 && !(k<3)) {
            SM3_State = SM3_On2;
         }
         else if (!A2) {
            SM3_State = SM3_Initial2;
         }
         else if (A2 && k <3) {
            SM3_State = SM3_Off2;
         }
         break;
      default:
         SM3_State = SM3_Initial2;
      } // Transitions

   switch(SM3_State) { // State actions
         case SM3_Initial2:
         B2=0;
k=0;
         break;
      case SM3_On2:
         k++;
B2=1;
         break;
      case SM3_Off2:
         k++;
B2=0;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum SM4_States { SM4_Initial3, SM4_On3, SM4_Off3 } SM4_State;

TickFct_State_Machine_4() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here.*/
static unsigned char l;
switch(SM4_State) { // Transitions
      case -1:
         SM4_State = SM4_Initial3;
         break;
         case SM4_Initial3:
         if (A3) {
            SM4_State = SM4_On3;
         }
         else if (!A3) {
            SM4_State = SM4_Initial3;
         }
         break;
      case SM4_On3:
         if (!A3) {
            SM4_State = SM4_Initial3;
         }
         else if (A3 && !(l<3)) {
            SM4_State = SM4_Off3;
            l=0;
         }
         else if (A3 && l<3) {
            SM4_State = SM4_On3;
         }
         break;
      case SM4_Off3:
         if (!A3) {
            SM4_State = SM4_Initial3;
         }
         else if (A3 && l<3) {
            SM4_State = SM4_Off3;
         }
         else if (A3 && !(l<3)) {
            SM4_State = SM4_On3;
            l=0;
         }
         break;
      default:
         SM4_State = SM4_Initial3;
      } // Transitions

   switch(SM4_State) { // State actions
         case SM4_Initial3:
         l=0;
B3=0;
         break;
      case SM4_On3:
         l++;
B3=1;
         break;
      case SM4_Off3:
         l++;
B3=0;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum SM5_States { SM5_Initial4, SM5_On4, SM5_Off4 } SM5_State;

TickFct_State_Machine_5() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here.*/
static unsigned char m;
switch(SM5_State) { // Transitions
      case -1:
         SM5_State = SM5_Initial4;
         break;
         case SM5_Initial4:
         if (!A4) {
            SM5_State = SM5_Initial4;
         }
         else if (A4) {
            SM5_State = SM5_On4;
         }
         break;
      case SM5_On4:
         if (!A4) {
            SM5_State = SM5_Initial4;
         }
         else if (A4 && m<3) {
            SM5_State = SM5_On4;
         }
         else if (A4 && !(m<3)) {
            SM5_State = SM5_Off4;
            m=0;
         }
         break;
      case SM5_Off4:
         if (A4 && !(m<3)) {
            SM5_State = SM5_On4;
            m=0;
         }
         else if (A4 && m<3) {
            SM5_State = SM5_Off4;
         }
         else if (!A4) {
            SM5_State = SM5_Initial4;
         }
         break;
      default:
         SM5_State = SM5_Initial4;
      } // Transitions

   switch(SM5_State) { // State actions
         case SM5_Initial4:
         m=0;
B4=0;
         break;
      case SM5_On4:
         B4=1;
m++;
         break;
      case SM5_Off4:
         B4=0;
m++;
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