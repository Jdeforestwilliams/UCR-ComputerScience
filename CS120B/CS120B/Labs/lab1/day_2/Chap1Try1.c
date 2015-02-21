#include "rims.h"

/* Write a C program for RIM that sets B0=1 whenever the numbers of 1s on A2, A1, and A0 is two or more (i.e., when A2A1A0 are 011, 110, 101, or 111). Hint: Use logical OR (||). Run the program in RIMS to test the program. */
   void main() {
       while(1) {
           char sum = 0;
           sum += A0;
           sum += A1;
           sum += A2;
           if (sum >= 2)
               B0=1;
           else 
               B0 = 0; 
       }
   }