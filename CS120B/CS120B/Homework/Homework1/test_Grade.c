#include "rims.h"

/* This is a sample program.  You can save/compile/run it, 
   modify it first, or just load a different program.      */

/* Sets B0 to 1 as quickly as possible when A0==1 and A1==0*/

/* Note that A0 - A7 can be set by clicking the switches to 
   the left, and B0 - B7 can be viewed as LEDs to the right
   (green corresponds to '1', red to '0').                 */

void main()
{
   while (1) { 
       B = 5; 
      B = ((A<<4)|B);
   }
}
