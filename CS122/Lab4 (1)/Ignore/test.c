#include "rims.h"

/* This is a sample program.  You can save/compile/run it, 
   modify it first, or just load a different program.      */

/* Sets B0 to 1 as quickly as possible when A0==1 and A1==0*/

/* Note that A0 - A7 can be set by clicking the switches to 
   the left, and B0 - B7 can be viewed as LEDs to the right
   (green corresponds to '1', red to '0').                 */

void main()
{
    unsigned char count = 0; 
    unsigned char counter = 0; 
    while(1){
      if (count < 0x80 && counter == 0){
          if (count == 0x00){
            B = 0x00; 
            count++; 
            counter = 0; 
          }  
          else {
            B = count;
            count *= 2;
            }
         }
      else if (!(count < 0x80) && counter == 0){
          
         }
  }
}
