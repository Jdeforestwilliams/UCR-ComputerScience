#include "RIMS.h"

void main(){
const unsigned char numVoltages = 5;
unsigned char voltages[5] = {0, 24, 17, 12, 6};
unsigned char i;
while(1) {
i = numVoltages - 1;
puts("Print array backwards: ");
while (i >= 0 && i < numVoltages){
puti(voltages[i]);
putc(' '); 
i = i - 1;
}
}
}
