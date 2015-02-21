#include "RIMS.h"

void main() {
unsigned long result;
unsigned char i;
while (1) {
result = 1;
i = 1;
while (i <= A) {
result = result * 2;
puts(" Iteration: "); puti(i); puts("\r\n");
i = i + 1;
}
puts("Result: "); puti(result); puts("\r\n\n");
B = result;
}
}