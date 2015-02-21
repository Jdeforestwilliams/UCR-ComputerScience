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