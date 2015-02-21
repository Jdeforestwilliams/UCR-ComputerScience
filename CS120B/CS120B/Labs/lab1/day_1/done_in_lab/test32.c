#include "RIMS.h"

void main(){
const unsigned char numVoltages = 5;
unsigned char voltages[5] = {0, 24, 17, 12, 6};
unsigned char highest;
unsigned char highestIndex;
unsigned char i;
while(1) {
highest = voltages[0];
puts("PrintArray: ");
for (i = 0; i < numVoltages; i = i + 1) {
if (voltages[i] > highest) {
highest= voltages[i];
highestIndex = i;
}
puti(voltages[i]); 
putc(' ');
}

B = highestIndex;
}
}
