/*	Adeja001_lab0_part5.c - 4/1/13
 *	Name & E-mail: Ariana Dejaco adeja001@ucr.edu
 *	CS Login: Adeja001
 *	Partner(s) Name & E-mail: Joshua DeForest-Williams jdefo002@ucr.edu 
 *	Lab Section: 22
 *	Assignment: Lab # 0   Exercise # Chapter 5 try # 37
 *	Exercise Description:Run the above program and observe that the printed output reflects the values of A7-A0. Next, add to the above program a new function definition named AryCountOnes, having the same two parameters as AryPrint and with a return type of unsigned char, that returns the number of array elements equal to 1. Update main to also set B to that number.
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include "RIMS.h"

void ACopyToArray(unsigned char Ary[]) {
Ary[0]=A0; Ary[1]=A1; Ary[2]=A2; Ary[3]=A3;
Ary[4]=A4; Ary[5]=A5; Ary[6]=A6; Ary[7]=A7;
return;
}

void AryPrint(unsigned char Ary[], unsigned char ArySize) {
unsigned char i;
for (i=0; i<ArySize; i++) {
puti(Ary[(ArySize-1)-i]); // (ArySize-1)-i: print in reverse
putc(' ');
}
putc('\n');
return;
}

unsigned char AryCountOnes(unsigned char Ary[], unsigned char ArySize)
{
    unsigned char returnVal = 0;
    int i;
    for( i = 0; i < ArySize; i++)
    {
        if(Ary[i] == 1)
          returnVal++; 
    }
    return returnVal;
}

void AryComplement(unsigned char Ary[], unsigned char ArySize)
{
    int i;
    for(i = 0; i < ArySize; i++)
    {
        if(Ary[i] == 0)
          Ary[i] = 1;
        else if(Ary[i] == 1)
          Ary[i] = 0; 
    }
}

void main(){
const unsigned char AASize = 8;
unsigned char AA[8];
while(1) {
B = CountOnes(A0, A1, A2);
puti(count); // ADD this statement
}
}
