#include "RIMS.h"

void main() {
int x = 25;

if( x != 50)
B0 = 1; 
else if(!(x == 50))
B1 = 1;
else if ((x > 5) && (x < 50) && (x != 25))
B2= 1; 
else if ((x > 5) && ( (x != 25) || (x != 50) ))
B3 = 1; 
}