
#include "IntVector.h"
#include <iostream>
#include <vector>
using namespace std;

void print( const IntVector & v )
{
  for ( int i = 0; i < v.size(); ++i )
    {
      cout << v.at(i) << " ";
    }
}

int main()
{
   const unsigned NUM_TESTS = 4;
   double score[NUM_TESTS];

   for(int i = 0; i < NUM_TESTS; i++){
      score[i] = 0;
   }

   IntVector v1;
   IntVector v2(5);
   IntVector v3(10,20);
   cout << "\nV2: ";
   print(v2);
   cout << "\nV3: ";
   print(v3);
   cout << endl;

   ////////////////////////test constructors/////////////////////

   score[0] = 40;

   bool param0 = true;
   bool param1 = true;
   bool param2 = true;

   if(v1.size() != 0){
      cout << "\nDefault constructor"
           << " - ERROR - not empty -8";
      param0 = false;
      score[0] -= 8;
   }

   for(int i = 0; i < 5; ++i){
   
      if(v2.at(i) != 0){
         param1 = false;
      }
   }
   if(!param1){
      cout << "\nConstructor with 1 parameter"
           << " - ERROR - did not set value -8";
      score[0] -= 8;
   }

   if((v2.size() != 5) && param1){
      cout << "\nConstructor with 1 parameter"
           << " - ERROR - did not set correct size -8";
      score[0] -= 8;
      param1 = false;
   }

   for(int i = 0; i < 10; i++){
      if(v3.at(i) != 20){
         param2 = false;
      }
   }
   if(!param2){
      cout << "\nConstructor with 2 parameter"
           << " - ERROR - did not set value -8";
      score[0] -= 8;
   }
   
   if((v3.size() != 10) && param2){
      cout << "\nConstructor with 2 parameter:"
           << " - ERROR - did not set correct size -8";
      score[0] -= 8;
      param2 = false;
   }

   if (param0 && param1 && param2){
      cout << "\nConstructors OK!" << endl;
   }
    
   ///////////////////////////////////////////////////////

   ////////////////////size + capacity////////////////////
   
   bool sizecap = true;
   score[1] = 20;
   
   IntVector v4(20,100);

   if(v4.size() != 20){
      
      score[1] -= 10;
      cout << "\nSIZE ERRROR -10";
      sizecap = false;
   }

   if(v4.capacity() != 20){
      
      score[1] -= 10;
      cout << "\nCAPACITY ERRROR -10";
      sizecap = false;
   }

   if (sizecap)
      cout << "\nSIZE + CAPACITY OK!" << endl;
    ///////////////////////////////////////////////////////


   //////////////////empty + at////////////////////////////

   IntVector v5;
   IntVector v6(28,5);
   score[2] = 20;
   bool emptyat = true;

   if(!v5.empty() || v6.empty()){
      score[2] -= 10;
      cout << "\nEMPTY ERROR -10";
      emptyat = false;
   }

   if(v6.at(24) != 5){
      score[2] -= 10;
      cout << "\nAT ERROR -10";
      emptyat = false;
   }

   if(emptyat){
       cout << "\nEMPTY + AT OK!" << endl;
   }

   //////////////////////////////////////////////////////////////

   ////////////////////front + back//////////////////////////////
   IntVector v7(40,12);
   bool frontback = true;
   score[3] = 20;

   if(v7.front() != 12){
      score[3] -= 10;
      cout << "\nFRONT ERROR -10";
      frontback = false;
   }

   if(v7.back() != 12){
      score[3] -= 10;
      cout << "\nBACK ERROR -10";
      frontback = false;
   }

   if(frontback)
      cout << "\nFRONT + BACK OK!" << endl;

   //////////////////////////////////////////////////////////

   //calculating score
   double total = 0;

   for (int i = 0; i < NUM_TESTS; i++){
      total += score[i];
   }
   cout << "\n\nTotal Score: " << total << endl << endl; //out of 100

   return 0;
}
