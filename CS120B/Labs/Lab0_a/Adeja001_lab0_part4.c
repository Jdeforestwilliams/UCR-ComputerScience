/*	Adeja001_lab0_part4.c - 4/1/13
 *	Name & E-mail: Ariana Dejaco adeja001@ucr.edu
 *	CS Login: Adeja001
 *	Partner(s) Name & E-mail: Josuha DeForest-Williams jdefo002@ucr.edu 
 *	Lab Section: 22
 *	Assignment: Lab #0  Exercise # Chapter 3 Try 17
 *	Exercise Description:
 *	Run the above program. Set A to 2 and note from the printed output that the inner while loop body executes twice, and the result is 4, which appears on B. Set A to 0 and note that the inner while loop body does not execute, and the result is 1. Set A to 15 and note that the result is 32768, though B does not show that value because B’s 8 bits cannot represent numbers larger than 255.
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include "RIMS.h"

void main() {
unsigned long result;
unsigned char i;
while (1) {
result = 1;
i = 1;
while (i <= A) {
result = result * 2;
puts(" Iteration: "); puti(i); puts("\r\n");
i = i + 1;
}
puts("Result: "); puti(result); puts("\r\n\n");
B = result;
}
}
