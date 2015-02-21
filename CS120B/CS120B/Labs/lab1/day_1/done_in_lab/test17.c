#include "RIMS.h"

void main() {
unsigned char count;
while (1) {
count = 0;
if (A0 == 1) {
count = count + 1;
}
else
if (A1 == 1) {
count = count + 1;
}
if (A2 == 1) {
count = count + 1;
}
B = count;
}
}