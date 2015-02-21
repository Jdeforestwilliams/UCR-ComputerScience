/*	Adeja001_lab0_part6.c - 4/5/13
 *	Name & E-mail: Ariana Dejaco adeja001@ucr.edu
 *	CS Login: Adeja001
 *	Partner(s) Name & E-mail:Joshua DeForest-Williams jdefo002@ucr.edu
 *	Lab Section: 22
 *	Assignment: Lab # 0  Exercise # 1 Chapter 1 
 *	Exercise Description:
 *  Write RIM C code that sets B0 to 1 only if A0-A3 are all 1's or if A5-A7 are all 1's (or if both situations are true. Using border and sample imput value combinations, test the written code with RIMS, and generate a timing diagram showing the test results 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include "RIMS.h"
void main(){
	while(1){
        if (A0 && A1 && A2 && A3) {
            B0 = 1;
        }
        else if (A4 && A5 && A6 && A7) {
            B0 = 1;
        }
        else {
            B0 = 0;
        }
	}
}
