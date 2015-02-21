#include "RIMS.h"

void main(){
unsigned char voltages[5] = {0, 24, 17, 12, 6};
unsigned char i;
unsigned int result;
while(1) {
i = 0;
result = 0;
while (i < 5) {
puti(voltages[i]); putc(' ');
result = result + voltages[i];
i = i + 1;
}
putc('\n');
B = result / 5;
}
}
