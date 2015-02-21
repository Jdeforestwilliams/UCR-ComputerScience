#include "RIMS.h"
unsigned char GetBit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);
}
    unsigned char BitNum; //The number used to identify which bit in A
    unsigned char MostConsecutive; //The number of the 1's in the most consecutive set. 
    unsigned char Count; // The number used to count how many 1's are consecutive in a set. 
void main(){
	while(1){
            Count = 0; // To reset the counter after each for loop. 
            for(BitNum=0; BitNum<8; BitNum++)
            {
                  if (GetBit(A, BitNum))
                  {
                      Count++; // To increment the variable for each "1" in a set. 
                      if (Count > MostConsecutive)
                      {
                           MostConsecutive = Count; //If the count in the current set is higher than a previous set. 
                       }
                   }
                   else
                   {
                       if (Count > MostConsecutive)
                       {
                             MostConsecutive = Count; // to double check if current set of 1's is higher than the most consecutive. 
                       }
                       Count = 0; 
                    }
              }
            B = MostConsecutive;
          }
}