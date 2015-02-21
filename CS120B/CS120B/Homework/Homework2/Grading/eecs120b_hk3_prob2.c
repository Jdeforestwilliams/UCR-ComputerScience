/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.5 --- 5/24/2013 16:52:19 PST
*/

#include "rims.h"


char enable = 0; 
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
         CS1_State = CS1_s1;
         break;
         case CS1_s1:
         if (!A0) {
            CS1_State = CS1_s1;
         }
         else if (A0 && (enable < 4)) {
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
         CS1_State = CS1_s1;
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
         CS2_State = CS2_s1;
         break;
         case CS2_s1:
         if (!A1) {
            CS2_State = CS2_s1;
         }
         else if (A1 && (enable < 4)) {
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
         CS2_State = CS2_s1;
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
         CS3_State = CS3_s1;
         break;
         case CS3_s1:
         if (!A2) {
            CS3_State = CS3_s1;
         }
         else if (A2 && (enable < 4)) {
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
         CS3_State = CS3_s1;
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
         CS4_State = CS4_s1;
         break;
         case CS4_s1:
         if (!A3) {
            CS4_State = CS4_s1;
         }
         else if (A3 && (enable < 4) ) {
            CS4_State = CS4_s2;
            l = 0; 
         }
         break;
      case CS4_s2:
         if (A3 && (l < 3) ) {
            CS4_State = CS4_s2;
         }
         else if (!A3 || !( enable < 4)) {
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
         CS4_State = CS4_s1;
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
         CS5_State = CS5_s1;
         break;
         case CS5_s1:
         if (!A4) {
            CS5_State = CS5_s1;
         }
         else if (A4 && (enable < 4)) {
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
         CS5_State = CS5_s1;
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

enum SM6_States { SM6_s1, SM6_s2, SM6_s3, SM6_s4, SM6_s5, SM6_s6, SM6_s7, SM6_s8, SM6_s9, SM6_s10, SM6_s11, SM6_s12, SM6_s13, SM6_s14, SM6_s15, SM6_s16, SM6_s17, SM6_s18, SM6_s19, SM6_s20, SM6_s21, SM6_s22, SM6_s23, SM6_s24, SM6_s25, SM6_s26, SM6_s27, SM6_s28, SM6_s29, SM6_s30, SM6_s31, SM6_s32, SM6_s33, SM6_s34, SM6_s35, SM6_s36, SM6_s37, SM6_s38, SM6_s39, SM6_s40, SM6_s41, SM6_s42, SM6_s43, SM6_s44, SM6_s45, SM6_s46, SM6_s47, SM6_s48, SM6_s49, SM6_s50, SM6_s51, SM6_s52, SM6_s53, SM6_s54, SM6_s55, SM6_s56, SM6_s57 } SM6_State;

TickFct_State_Machine_6() {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here.*/
char test = 0; 
switch(SM6_State) { // Transitions
      case -1:
         SM6_State = SM6_s1;
         break;
         case SM6_s1:
         if (A0) {
            SM6_State = SM6_s2;
         }
         else if (!A0; ) {
            SM6_State = SM6_s3;
         }
         break;
      case SM6_s2:
         if (A1) {
            SM6_State = SM6_s4;
         }
         else if (!A1) {
            SM6_State = SM6_s5;
         }
         break;
      case SM6_s3:
         if (A1) {
            SM6_State = SM6_s35;
         }
         else if (!A1) {
            SM6_State = SM6_s34;
         }
         break;
      case SM6_s4:
         if (A2) {
            SM6_State = SM6_s6;
         }
         else if (!A2) {
            SM6_State = SM6_s7;
         }
         break;
      case SM6_s5:
         if (A2) {
            SM6_State = SM6_s21;
         }
         else if (!A2) {
            SM6_State = SM6_s20;
         }
         break;
      case SM6_s6:
         if (A3) {
            SM6_State = SM6_s8;
         }
         else if (!A3) {
            SM6_State = SM6_s9;
         }
         break;
      case SM6_s7:
         if (A3) {
            SM6_State = SM6_s15;
         }
         else if (!A3) {
            SM6_State = SM6_s14;
         }
         break;
      case SM6_s8:
         if (A4) {
            SM6_State = SM6_s10;
         }
         else if (!A4. ) {
            SM6_State = SM6_s11;
         }
         break;
      case SM6_s9:
         if (A4) {
            SM6_State = SM6_s13;
         }
         else if (!A4) {
            SM6_State = SM6_s12;
         }
         break;
      case SM6_s10:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s11:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s12:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s13:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s14:
         if (A4) {
            SM6_State = SM6_s18;
         }
         else if (!A4) {
            SM6_State = SM6_s19;
         }
         break;
      case SM6_s15:
         if (A4) {
            SM6_State = SM6_s16;
         }
         else if (!A4) {
            SM6_State = SM6_s17;
         }
         break;
      case SM6_s16:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s17:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s18:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s19:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s20:
         if (A3) {
            SM6_State = SM6_s29;
         }
         else if (!A3) {
            SM6_State = SM6_s28;
            
         }
         break;
      case SM6_s21:
         if (A3) {
            SM6_State = SM6_s22;
         }
         else if (!A3) {
            SM6_State = SM6_s23;
         }
         break;
      case SM6_s22:
         if (A4) {
            SM6_State = SM6_s25;
         }
         else if (!A4) {
            SM6_State = SM6_s24;
         }
         break;
      case SM6_s23:
         if (A4) {
            SM6_State = SM6_s26;
         }
         else if (!A4) {
            SM6_State = SM6_s27;
         }
         break;
      case SM6_s24:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s25:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s26:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s27:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s28:
         if (1) {
            SM6_State = SM6_s32;
            A4
         }
         else if (!A4;) {
            SM6_State = SM6_s33;
         }
         break;
      case SM6_s29:
         if (A4) {
            SM6_State = SM6_s30;
         }
         else if (!A4) {
            SM6_State = SM6_s31;
         }
         break;
      case SM6_s30:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s31:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s32:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s33:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s34:
         if (!A2) {
            SM6_State = SM6_s36;
         }
         else if (A2) {
            SM6_State = SM6_s37;
         }
         break;
      case SM6_s35:
         if (A2) {
            SM6_State = SM6_s39;
         }
         else if (!A2) {
            SM6_State = SM6_s38;
         }
         break;
      case SM6_s36:
         if (!A3) {
            SM6_State = SM6_s40;
         }
         else if (A3) {
            SM6_State = SM6_s41;
         }
         break;
      case SM6_s37:
         if (!A3) {
            SM6_State = SM6_s42;
         }
         else if (A3) {
            SM6_State = SM6_s43;
         }
         break;
      case SM6_s38:
         if (!A3) {
            SM6_State = SM6_s44;
         }
         else if (A3) {
            SM6_State = SM6_s45;
         }
         break;
      case SM6_s39:
         if (!A3) {
            SM6_State = SM6_s46;
         }
         else if (A3) {
            SM6_State = SM6_s47;
         }
         break;
      case SM6_s40:
         if (!A4) {
            SM6_State = SM6_s48;
         }
         else if (A4) {
            SM6_State = SM6_s49;
         }
         break;
      case SM6_s41:
         if (!A4) {
            SM6_State = SM6_s50;
         }
         else if (A4) {
            SM6_State = SM6_s51;
         }
         break;
      case SM6_s42:
         break;
      case SM6_s43:
         if (!A4) {
            SM6_State = SM6_s54;
         }
         else if (A4) {
            SM6_State = SM6_s55;
         }
         break;
      case SM6_s44:
         if (!A4) {
            SM6_State = SM6_s52;
         }
         else if (A4) {
            SM6_State = SM6_s53;
         }
         break;
      case SM6_s45:
         if (!A4) {
            SM6_State = SM6_s56;
         }
         else if (A4) {
            SM6_State = SM6_s57;
         }
         break;
      case SM6_s46:
         break;
      case SM6_s47:
         break;
      case SM6_s48:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s49:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s50:
         break;
      case SM6_s51:
         break;
      case SM6_s52:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s53:
         break;
      case SM6_s54:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s55:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s56:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      case SM6_s57:
         if (1) {
            SM6_State = SM6_s1;
         }
         break;
      default:
         SM6_State = SM6_s1;
      } // Transitions

   switch(SM6_State) { // State actions
         case SM6_s1:
         break;
      case SM6_s2:
         enable = 1; 
         break;
      case SM6_s3:
         enable = 0; 
         break;
      case SM6_s4:
         enable =2; 
         break;
      case SM6_s5:
         enable = 1; 
         break;
      case SM6_s6:
         enable = 3; 
         break;
      case SM6_s7:
         enable = 2;
         break;
      case SM6_s8:
         enable = 4; 
         break;
      case SM6_s9:
         enable = 3; 
         break;
      case SM6_s10:
         enable =5; 
         break;
      case SM6_s11:
         enable = 4; 
         break;
      case SM6_s12:
         enable = 3;
         break;
      case SM6_s13:
         enable = 4; 
         break;
      case SM6_s14:
         enable = 2; 
         break;
      case SM6_s15:
         enable = 3;
         break;
      case SM6_s16:
         enable = 4;
         break;
      case SM6_s17:
         enable= 3; 
         break;
      case SM6_s18:
         enable = 3; 
         break;
      case SM6_s19:
         enable = 2; 
         break;
      case SM6_s20:
         enable = 1; 
         break;
      case SM6_s21:
         enable = 2;
         break;
      case SM6_s22:
         enable = 3; 
         break;
      case SM6_s23:
         enable = 2;
         break;
      case SM6_s24:
         enable = 3;
         break;
      case SM6_s25:
         enable = 4;
         break;
      case SM6_s26:
         enable = 3;
         break;
      case SM6_s27:
         enable = 2; 
         break;
      case SM6_s28:
         enable = 1; 
         break;
      case SM6_s29:
         enable = 2; 
         break;
      case SM6_s30:
         enable = 3; 
         break;
      case SM6_s31:
         enable = 2; 
         break;
      case SM6_s32:
         enable = 2; 
         break;
      case SM6_s33:
         enable = 1;
         break;
      case SM6_s34:
         enable = 0; 
         break;
      case SM6_s35:
         enable = 1;
         break;
      case SM6_s36:
         enable = 0; 
         break;
      case SM6_s37:
         enable = 1; 
         break;
      case SM6_s38:
         enable = 1;

         break;
      case SM6_s39:
         enable = 2; 
         break;
      case SM6_s40:
         enable = 0; 
         break;
      case SM6_s41:
         enable = 1; 
         break;
      case SM6_s42:
         enable = 1; 
         break;
      case SM6_s43:
         enable = 2; 
         break;
      case SM6_s44:
         enable = 1; 
         break;
      case SM6_s45:
         enable = 2; 
         break;
      case SM6_s46:
         enable = 2; 
         break;
      case SM6_s47:
         enable = 3; 
         break;
      case SM6_s48:
         enable = 0; 
         break;
      case SM6_s49:
         enable = 1; 
         break;
      case SM6_s50:
         enable = 1; 
         break;
      case SM6_s51:
         enable = 2; 
         break;
      case SM6_s52:
         enable = 1; 
         break;
      case SM6_s53:
         enable = 2; 
         break;
      case SM6_s54:
         enable = 2; 
         break;
      case SM6_s55:
         enable = 3; 
         break;
      case SM6_s56:
         enable = 2; 
         break;
      case SM6_s57:
         enable = 3; 
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
   SM6_State = -1;
   while(1) {
      TickFct_CS_1();
      TickFct_CS_2();
      TickFct_CS_3();
      TickFct_CS_4();
      TickFct_CS_5();
      TickFct_State_Machine_6();
      while (!TimerFlag);
      TimerFlag = 0;
   }
}