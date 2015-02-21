#include "rims.h"

//More understandable miles driven statistics program using functions
typedef unsigned char uchar;
typedef unsigned short ushort;

ushort MilesDrivenGetHighest(ushort milesDriven[], uchar milesDrivenSize);
ushort MilesDrivenGetLowest (ushort milesDriven[], uchar milesDrivenSize);
ushort MilesDrivenGetAvg
(ushort milesDriven[], uchar milesDrivenSize);

// more-understandable main function for the miles driven statistics program
void main(){
uchar milesDrivenSize = 20;
ushort milesDriven[20] = // in trillions
{ 2144, 2172, 2247, 2296, 2358, 2423, 2486, 2562, 2632, 2691,//1990-99
2747, 2781, 2855, 2890, 2962, 2989, 3014, 3029, 2973, 2979};//2000-09
ushort highest, lowest, sum, avg;
while(1) {
highest = MilesDrivenGetHighest(milesDriven, milesDrivenSize );
lowest = MilesDrivenGetLowest (milesDriven, milesDrivenSize );
avg
= MilesDrivenGetAvg
(milesDriven, milesDrivenSize );
puts("Highest: "); puti(highest); puts("\r\n");
puts("Lowest: "); puti(lowest); puts("\r\n");
puts("Average: "); puti(avg);
puts("\r\n\n");
}
}

ushort MilesDrivenGetHighest(ushort milesDriven[], uchar milesDrivenSize )
{
ushort highest;
uchar i;
highest = milesDriven[0];
for (i=0; i<milesDrivenSize; i++) {
if (milesDriven[i] > highest) {
highest = milesDriven[i];
}
}
return(highest);
}

ushort MilesDrivenGetLowest (ushort milesDriven[], uchar milesDrivenSize )
{
   ushort lowest; 
   uchar i;
   lowest = milesDriven[0];
   for (i =0; i<milesDrivenSize; i++){
   if (milesDriven[i] < lowest) {
       lowest = milesDriven[i];
   }
   }
   
return(lowest); // FIXME Finish this function. 9/1/11 Alan S.
}

ushort MilesDrivenGetAvg
(ushort milesDriven[], uchar milesDrivenSize )
{
    ushort avg;
    uchar i;
    avg = 0; 
    for (i = 0; i < milesDrivenSize; i++){
        avg += milesDriven[i];
    }
    avg = avg / i; 
    
return(avg); // FIXME Finish this function. 9/1/11 Alan S.
}
