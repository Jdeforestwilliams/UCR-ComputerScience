#include "RIMS.h"

void SetBToAllOnes() {
//unsigned char B; // This declaration blocks out the global B
B = 255;
return;
}

void main() {
while (1) {
SetBToAllOnes();
}
}