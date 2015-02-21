#include "rims.h"

// Initial driving statistics program, with yearl-info spread across 2 arrays
typedef unsigned char uchar;
typedef unsigned short ushort;

void main(){
uchar yearsInfoSize = 20;
ushort milesDriven[20] = // in billions
{ 2144, 2172, 2247, 2296, 2358, 2423, 2486, 2562, 2632, 2691,
2747, 2781, 2855, 2890, 2962, 2989, 3014, 3029, 2973, 2979 };
uchar duiDeathsSize = 20;
uchar duiDeaths[20] = // in thousands
{ 18, 16, 14, 14, 13, 13, 13, 13, 13, 13,
// 1990-1999
13, 13, 13, 13, 13, 14, 13, 13, 12, 11 }; // 2000-2009
ushort baseyear = 1990;
uchar i;
while(1) {
i = A;
if (i < yearsInfoSize) { // Ensure valid index
puts("Year: "); puti(baseyear+i); puts("\n");
puts(" "); puti(milesDriven[i]); puts(" billion miles driven\n");
puts(" "); puti(duiDeaths[i]);
puts(" thousand DUI deaths\n");
}
while (A == i) {}; // Print once, then wait for A to change
}
}