#include "rims.h"


 typedef unsigned char uchar;

// high and low parameters are declared as POINTERS to uchars
void Nibbles(uchar num, uchar *high, uchar *low) {
*high = num >> 4; // Note the "*" before high
*low = num & 0x0F; // Note the "*" before low
return;
}

uchar i, j;
void main(){
uchar num;
while(1) {
num = A;
Nibbles(num, &i, &j); // Passing i/j ADDRESSES
puts("High nibble: "); puti(i);
puts(" Low nibble: "); puti(j); puts("\r\n");
while (num == A) {} // Print once; wait for change
}
}