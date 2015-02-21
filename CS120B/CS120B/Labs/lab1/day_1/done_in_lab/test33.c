#include "RIMS.h"

void main(){
const unsigned char numVoltages = 5;
unsigned char voltages[5] = {0, 24, 17, 12, 6};
unsigned char i;
while(1) {

puts("Print array backwards: ");
for (i = numVoltages - 1;i >= 0 && i < numVoltages; i--){
puti(voltages[i]);
putc(' '); 
}
}
}
