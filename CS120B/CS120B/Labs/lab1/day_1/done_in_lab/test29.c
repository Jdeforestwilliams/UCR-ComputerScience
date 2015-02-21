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
if (voltages[i] > 15) {

highestIndex = i; 
}
i = i + 1;
}
B = highestIndex;
i = numVoltages - 1;
puts("Print array backwards: ");
while (i >= 0){
puti(voltages[i]);
putc(' '); 
i--;
}

}
}
