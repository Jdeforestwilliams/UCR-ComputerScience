/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.5 --- 5/29/2013 14:14:5 PST
*/

#include "rims.h"


/*This code will be shared between state machines.*/
unsigned char TimerFlag = 0;
void TimerISR() {
   TimerFlag = 1;
}


enum CS1_States { CS1_s1, CS1_s2, CS1_s3 } CS1_State;

TickFct_CS_1() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define User Variables and Functions For this State Machine Here.*/
static char i; 
switch(CS1_State) { // Transitions
      case -1:
         CS1_State = CS1_s2;
         break;
         case CS1_s1:
         if (!A0) {
            CS1_State = CS1_s1;
         }
         else if (A0) {
            CS1_State = CS1_s2;
            i = 0; 
         }
         break;
      case CS1_s2:
         if (A0 && (i < 3)) {
            CS1_State = CS1_s2;
         }
         else if (A0 & !(i < 3)) {
            CS1_State = CS1_s3;
            i = 0; 
         }
         else if (!A0) {
            CS1_State = CS1_s1;
         }
         break;
      case CS1_s3:
         if (A0 && (i <3) ) {
            CS1_State = CS1_s3;
            B0 = 0; 
         }
         else if (A0 && !(i < 3)) {
            CS1_State = CS1_s2;
            i = 0; 
         }
         else if (!A0) {
            CS1_State = CS1_s1;
         }
         break;
      default:
         CS1_State = CS1_s2;
      } // Transitions

   switch(CS1_State) { // State actions
         case CS1_s1:
         B0 = 0;
         break;
      case CS1_s2:
         i++;
B0 = 1;
         break;
      case CS1_s3:
         i++; 
B0 = 0; 
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum CS2_States { CS2_s1, CS2_s2, CS2_s3 } CS2_State;

TickFct_CS_2() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here.*/
static char j; 
switch(CS2_State) { // Transitions
      case -1:
         CS2_State = CS2_s2;
         break;
         case CS2_s1:
         if (!A1) {
            CS2_State = CS2_s1;
         }
         else if (A1) {
            CS2_State = CS2_s2;
            j = 0; 
         }
         break;
      case CS2_s2:
         if (!A1) {
            CS2_State = CS2_s1;
         }
         else if (A1 && (j < 3) ) {
            CS2_State = CS2_s2;
         }
         else if (A1 && !(j < 3) ) {
            CS2_State = CS2_s3;
            j = 0; 
         }
         break;
      case CS2_s3:
         if (!A1) {
            CS2_State = CS2_s1;
         }
         else if (A1 && (j < 3) ) {
            CS2_State = CS2_s3;
         }
         else if (A1 && !(j < 3) ) {
            CS2_State = CS2_s2;
            j = 0; 
         }
         break;
      default:
         CS2_State = CS2_s2;
      } // Transitions

   switch(CS2_State) { // State actions
         case CS2_s1:
         B1 = 0; 
         break;
      case CS2_s2:
         j++;
B1 = 1; 
         break;
      case CS2_s3:
         j++; 
B1 = 0; 
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum CS3_States { CS3_s1, CS3_s2, CS3_s3 } CS3_State;

TickFct_CS_3() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here.*/
char k; 
switch(CS3_State) { // Transitions
      case -1:
         CS3_State = CS3_s2;
         break;
         case CS3_s1:
         if (!A2) {
            CS3_State = CS3_s1;
         }
         else if (A2) {
            CS3_State = CS3_s2;
            k= 0; 
         }
         break;
      case CS3_s2:
         if (!A2) {
            CS3_State = CS3_s1;
         }
         else if (A2 && (k < 3) ) {
            CS3_State = CS3_s2;
         }
         else if (A2 && !(k < 3) ) {
            CS3_State = CS3_s3;
            k = 0; 
         }
         break;
      case CS3_s3:
         if (!A2 ) {
            CS3_State = CS3_s1;
            B2 = 0; 
         }
         else if (A2 && (k < 3) ) {
            CS3_State = CS3_s3;
         }
         else if (A2 && !(k < 3) ) {
            CS3_State = CS3_s2;
            k = 0; 
         }
         break;
      default:
         CS3_State = CS3_s2;
      } // Transitions

   switch(CS3_State) { // State actions
         case CS3_s1:
         B2 = 0; 
         break;
      case CS3_s2:
         k++;
B2 = 1; 
         break;
      case CS3_s3:
         k++; 
B2 = 0; 
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum CS4_States { CS4_s1, CS4_s2, CS4_s3 } CS4_State;

TickFct_CS_4() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here.*/
static char l; 
switch(CS4_State) { // Transitions
      case -1:
         CS4_State = CS4_s2;
         break;
         case CS4_s1:
         if (!A3) {
            CS4_State = CS4_s1;
         }
         else if (A3) {
            CS4_State = CS4_s2;
            l = 0; 
         }
         break;
      case CS4_s2:
         if (A3 && (l < 3) ) {
            CS4_State = CS4_s2;
         }
         else if (!A3) {
            CS4_State = CS4_s1;
            B3 = 0; 
         }
         else if (A3 && !(l < 3) ) {
            CS4_State = CS4_s3;
            l = 0; 
         }
         break;
      case CS4_s3:
         if (A3 && (l < 3) ) {
            CS4_State = CS4_s3;
         }
         else if (A3 && !(l < 3) ) {
            CS4_State = CS4_s2;
            l = 0; 
         }
         else if (!A3) {
            CS4_State = CS4_s1;
            B3 = 0; 
         }
         break;
      default:
         CS4_State = CS4_s2;
      } // Transitions

   switch(CS4_State) { // State actions
         case CS4_s1:
         B3 = 0; 
         break;
      case CS4_s2:
         l++; 
B3 = 1; 
         break;
      case CS4_s3:
         l++;
B3 = 0; 
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}

enum CS5_States { CS5_s1, CS5_s2, CS5_s3 } CS5_State;

TickFct_CS_5() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here.*/
static char p ; 
switch(CS5_State) { // Transitions
      case -1:
         CS5_State = CS5_s2;
         break;
         case CS5_s1:
         if (!A4) {
            CS5_State = CS5_s1;
         }
         else if (A4) {
            CS5_State = CS5_s2;
            p=0; 
         }
         break;
      case CS5_s2:
         if (A4 && (p < 3) ) {
            CS5_State = CS5_s2;
         }
         else if (!A4) {
            CS5_State = CS5_s1;
            B4 = 0; 
         }
         else if (A4 && !(p < 3) ) {
            CS5_State = CS5_s3;
            p = 0; 
         }
         break;
      case CS5_s3:
         if (A4 && (p < 3) ) {
            CS5_State = CS5_s3;
         }
         else if (!A4) {
            CS5_State = CS5_s1;
            B4 = 0;
         }
         else if (A4 && !(p < 3) ) {
            CS5_State = CS5_s2;
            p= 0; 
         }
         break;
      default:
         CS5_State = CS5_s2;
      } // Transitions

   switch(CS5_State) { // State actions
         case CS5_s1:
         B4 = 0; 
         break;
      case CS5_s2:
         B4 = 1;
p++;

         break;
      case CS5_s3:
         B4 = 0;
p++;

         break;
      default: // ADD default behaviour below
         break;
   } // State actions
}
int main() {
   B = 0; //Init outputs
   TimerSet(1000);
   TimerOn();
   CS1_State = -1;
   CS2_State = -1;
   CS3_State = -1;
   CS4_State = -1;
   CS5_State = -1;
   while(1) {
      TickFct_CS_1();
      TickFct_CS_2();
      TickFct_CS_3();
      TickFct_CS_4();
      TickFct_CS_5();
      while (!TimerFlag);
      TimerFlag = 0;
   }
}