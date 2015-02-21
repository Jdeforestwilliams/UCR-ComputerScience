#include "rims.h"

void LedsTick() {
unsigned char leds = 1;
leds = (leds == 8) ? 1 : leds * 2;
B = leds;
}

void main(){
while(1){
LedsTick();
}
}