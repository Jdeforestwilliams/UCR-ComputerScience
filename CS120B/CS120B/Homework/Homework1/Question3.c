#include "RIMS.h"

enum Count_States{ CNT_state_0, CNT_state_1, CNT_state_2 } CNT_State;
void Counter_State() 
{ 
  switch(CNT_State) { // Transitions 
      case -1:  // Initial transition         
         CNT_State = CNT_state_0; 
         break;  
      case CNT_state_0:  
         if (!A0) {   
            CNT_State = CNT_state_0;
         }         
         else if (A0) {   
            CNT_State = CNT_state_1;
         }       
           break;     
      case CNT_state_1:
          if (!A0)
          {
             CNT_State = CNT_state_0;
          }
          else
          {
             CNT_State = CNT_state_2; 
           }
             break; 
      case CNT_state_2: 
           if (!A0)
           {
             CNT_State = CNT_state_0;
           }
           else 
           {
             CNT_State = CNT_state_2;
           }
           break; 
      default:  
            CNT_State = -1; 
            break; 
     } // Transitions
 switch(CNT_State) { // State actions
 case CNT_state_0: 
   break; 
 case CNT_state_1: 
   B = B+1; 
   break; 
 case CNT_state_2: 
   break; 
 default:
   break; } // State actions
}
void main() {
 B = 0; // Initialize outputs
 CNT_State = -1; // Indicates initial call
 while(1)
 {
     Counter_State(); } 
}
