/*	[file_name].c - [date]
 *	Name & E-mail:
 *	CS Login: 
 *	Partner(s) Name & E-mail:
 *	Lab Section: 
 *	Assignment: Lab #  Exercise # 
 *	Exercise Description:
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
<your code hereafter> 
#include "rims.h"

/* This is a sample program.  You can save/compile/run it, 
   modify it first, or just load a different program.      */

/* Sets B0 to 1 as quickly as possible when A0==1 and A1==0*/

/* Note that A0 - A7 can be set by clicking the switches to 
   the left, and B0 - B7 can be viewed as LEDs to the right
   (green corresponds to '1', red to '0').                 */

void main()
{
   while (1) { 
      B0 = A0;
      B1 = A1;
      B2 = A2;
      B3 = A3; 
      B4 = A4; 
      B5 = A5;
      B6 = A6;
      B7 = A7;
   }
}
