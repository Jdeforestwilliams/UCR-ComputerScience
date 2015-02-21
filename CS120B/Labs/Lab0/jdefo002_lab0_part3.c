/*	jdefo002_lab0_part3.c - 4/1/13
 *	Name & E-mail: Josuha DeForest-Williams jdefo002@ucr.edu
 *	CS Login: Jdefo002
 *	Partner(s) Name & E-mail: Ariana Dejaco adeja001@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab #0  Exercise # Chapter 3 Try 17
 *	Exercise Description:
 *	Run the above program, change A’s switches to different values, and observe the output LEDs. Use the step functionality to observe that only one of the three branches’ will have its statements executed.
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */#include "RIMS.h"

void main() {
while (1) {
if (A <= 100) {
B0 = 1;
B1 = 0;
B2 = 0;
}
else if (A <= 200) {
B0 = 0;
B1 = 1;
B2 = 0;
}
else {
B0 = 0;
B1 = 0;
B2 = 1;
}
}
}
