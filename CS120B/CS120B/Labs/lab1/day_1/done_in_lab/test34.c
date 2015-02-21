#include "RIMS.h"

// function definition
unsigned char CountOnes(unsigned char x,
unsigned char y, unsigned char z) {
unsigned char count;
count = 0;
if (x == 1) {
count = count + 1;
}
if (y == 1) {
count = count + 1;
}
if (z == 1) {
count = count + 1;
}
return count;
}

void main() {
while (1) {
B = CountOnes(A0, A1, A2); // function call
}
}