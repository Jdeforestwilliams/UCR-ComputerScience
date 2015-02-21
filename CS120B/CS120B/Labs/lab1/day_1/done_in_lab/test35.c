#include "RIMS.h"

unsigned char CelsToFahr ( unsigned char F )
{
    return ((9 * F) / 5) + 32;
}    

void main() {
while (1) {
B = CelsToFahr(A); // Celsius to Fahrenheit conversion
}
}