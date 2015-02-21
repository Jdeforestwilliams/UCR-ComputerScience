#include "RIMS.h"

void main(){
const unsigned char numVoltages = 5;
unsigned char voltages[5] = {0, 24, 17, 12, 6};
unsigned char lowest;
unsigned char i;
while(1) {
lowest = voltages[0];
i = 0;
while (i < numVoltages) {
if (voltages[i] < lowest) {
lowest = voltages[i];
}
i = i + 1;
}
B = lowest;
}
}
