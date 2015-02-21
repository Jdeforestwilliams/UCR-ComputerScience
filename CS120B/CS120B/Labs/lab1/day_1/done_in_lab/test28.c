#include "RIMS.h"

void main(){
const unsigned char numVoltages = 5;
unsigned char voltages[5] = {0, 24, 17, 12, 6};
unsigned char highest;
unsigned char highestIndex;
unsigned char i;
while(1) {
highestIndex = 0;
highest = voltages[0];
i = 0;
while (i < numVoltages) {
if (voltages[i] > highest) {
highest = voltages[i];
highestIndex = i; 
}
i = i + 1;
}
B = highestIndex;
}
}
