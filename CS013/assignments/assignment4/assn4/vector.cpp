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
   const unsigned NUM_TESTS = 15;
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

   score[0] = 5;

   bool param0 = true;
   bool param1 = true;
   bool param2 = true;

   if(v1.size() != 0){
      cout << "\nDefault constructor"
           << " - ERROR - not empty -1";
      param0 = false;
      score[0] -= 1;
   }

   for(int i = 0; i < 5; ++i){
   
      if(v2.at(i) != 0){
         param1 = false;
      }
   }
   if(!param1){
      cout << "\nConstructor with 1 parameter"
           << " - ERROR - did not set value -1";
      score[0] -= 1;
   }

   if((v2.size() != 5) && param1){
      cout << "\nConstructor with 1 parameter"
           << " - ERROR - did not set correct size -1";
      score[0] -= 1;
      param1 = false;
   }

   for(int i = 0; i < 10; i++){
      if(v3.at(i) != 20){
         param2 = false;
      }
   }
   if(!param2){
      cout << "\nConstructor with 2 parameter"
           << " - ERROR - did not set value -1";
      score[0] -= 1;
   }
   
   if((v3.size() != 10) && param2){
      cout << "\nConstructor with 2 parameter:"
           << " - ERROR - did not set correct size -1";
      score[0] -= 1;
      param2 = false;
   }

   if (param0 && param1 && param2){
      cout << "\nConstructors OK!" << endl;
   }
    
   ///////////////////////////////////////////////////////

   ////////////////////size + capacity////////////////////
   
   bool sizecap = true;
   score[1] = 10;
   
   IntVector v4(20,100);

   if(v4.size() != 20){
      
      score[1] -= 5;
      cout << "\nSIZE ERRROR -5";
      sizecap = false;
   }

   if(v4.capacity() != 20){
      
      score[1] -= 5;
      cout << "\nCAPACITY ERRROR -5";
      sizecap = false;
   }

   if (sizecap)
      cout << "\nSIZE + CAPACITY OK!" << endl;
    ///////////////////////////////////////////////////////


   //////////////////empty + at////////////////////////////

   IntVector v5;
   IntVector v6(28,5);
   score[2] = 10;
   bool emptyat = true;

   if(!v5.empty() || v6.empty()){
      score[2] -= 5;
      cout << "\nEMPTY ERROR -5";
      emptyat = false;
   }

   if(v6.at(24) != 5){
      score[2] -= 5;
      cout << "\nAT ERROR -5";
      emptyat = false;
   }

   if(emptyat){
       cout << "\nEMPTY + AT OK!" << endl;
   }

   //////////////////////////////////////////////////////////////

   ////////////////////front + back//////////////////////////////
   IntVector v7(40,12);
   bool frontback = true;
   score[3] = 10;

   if(v7.front() != 12){
      score[3] -= 5;
      cout << "\nFRONT ERROR -5";
      frontback = false;
   }

   if(v7.back() != 12){
      score[3] -= 5;
      cout << "\nBACK ERROR -5";
      frontback = false;
   }

   if(frontback)
      cout << "\nFRONT + BACK OK!" << endl;

   //////////////////////////////////////////////////////////

   ////////////////expand + reserve + resize/////////////////

   bool ex_rv_rs = true;
   IntVector v8(10,5);
   v8.reserve(5);

   score[4] = 10;//score for expand
   score[5] = 5;//score for reserve
   score[6] = 10;//score for resize

   //reserve
   if(v8.capacity() != 10){
      cout << "\nRESERVE ERROR #1 -5" << endl;
      ex_rv_rs = false;
      score[5] = 0;
   }

   v8.reserve(12);

   if(v8.capacity() != 20){
      cout << "\nRESERVE ERROR #2 -5" << endl;
      ex_rv_rs = false;
      score[5] = 0;
   }

   v8.reserve(100);

   if(v8.capacity() != 100){
      cout << "\nRESERVE ERROR #3 -5" << endl;
      ex_rv_rs = false;
      score[5] = 0;      
   }

   if(ex_rv_rs){
      cout << "\nRESERVE - OK!" << endl;
   }

   //resize

   IntVector v9(2,5);
   bool resizing = true;

   v9.resize(8);

   if((v9.size() != 8) || (v9.at(6) != 0) || (v9.at(1) != 5)){
      score[6] -= 2.5;
      cout << "\nRESIZE ERROR with 1 parameter -2.5" << endl;
      resizing = false;
   }

   IntVector v10(10,5);

   v10.resize(8,7);

   if((v10.capacity() != 10) || (v10.size() != 8) || (v10.at(3) != 5)){
      score[6] -= 2.5;
      cout << "\nRESIZE ERROR with 2 parameter a -2.5" << endl;
      resizing = false;
   }

   v10.resize(25, 10);
   if((v10.capacity() != 25) || (v10.size() != 25) || 
      (v10.at(3) != 5) || (v10.at(20) != 10)){
      score[6] -= 2.5;
      cout << "\nRESIZE ERROR with 2 parameter b -2.5" << endl;
      resizing = false;
   }

   v10.resize(26, 11);
   if((v10.capacity() != 50) || (v10.size() != 26) || 
      (v10.at(3) != 5) || (v10.at(20) != 10) || (v10.at(25) != 11)){
      score[6] -= 2.5;
      cout << "\nRESIZE ERROR with 2 parameter c -2.5" << endl;
      resizing = false;
   }
   if(resizing){
      cout << "\nRESIZE - OK!" << endl;
   }

   if((resizing) && (ex_rv_rs)){
      cout<<"\nEXPAND = OK!" << endl;
   }
   else{
      cout << "\n possible expand error?" << endl;
      score[4] -= 10;
   }

   /////////////////////////////////////////////////////////////////

   ///////////////////////insert////////////////////////////////////
   
   IntVector v11(10, 8);
   score[7] = 5; //score for insert
   v11.insert(5, 3);

   if((v11.size() != 11) || (v11.at(5) != 3)){
      score[7] -= 5;
      cout << "\nINSERT ERROR -5" << endl;
      resizing = false;
   }
   else{
      cout << "\nINSERT = OK!" << endl;
   }

   /////////////////////////////////////////////////////////////////


    /////////////erase//////////////////////////////////////////////
   score[8] = 5; //score for erase
   IntVector v12;
   bool erasing = true;
   v12.insert(0, 1);
   v12.insert(1, 2);
   v12.insert(2, 3);

   if(v12.size() != 3){
      score[7] -= 5;
      cout << "\nINSERT ERROR b -5" << endl;
      resizing = false;
   }
   else{
      v12.erase(1);
      if((v12.size() != 2) || (v12.at(0) != 1) || (v12.at(1) != 3)){
         score[8] -= 5;
         cout << "\nERASE ERROR -5" << endl;
         erasing = false;
      }
   }

   if (erasing){
      cout << "\nERASE = OK!" << endl;
   }

   ////////////////////////////////////////////////////////////////////


   ///////////////////push_back////////////////////////////////////////

   IntVector v13(4, 2);
   bool pb = true;
   score[9] = 5; //score for push_back

   v13.push_back(100);

   if((v13.at(4) != 100) || (v13.size() != 5)){
      score[9] -= 5;
      cout << "\nPUSH_BACK ERROR -5" << endl;
      pb = false;
   }
   else{
      cout << "\nPUSH_BACK = OK!" << endl;
   }

   ////////////////////////////////////////////////////////////////////

   ////////////////pop_back/////////////////////////////////
    
   IntVector v14(9, 9);
   score[10] = 5;//score for pop_back
   v14.pop_back();

   if(v14.size() != 8){
      score[10] -= 5;
      cout << "\nPOP_BACK ERROR -5" << endl;
   }
   else{
      cout << "\nPOP_BACK = OK!" << endl;
   }

   //////////////////////////////////////////////////////////


   //////////////clear////////////////////////////////////////////////

   IntVector v15(60,2);
   score[11] = 5;//score for clear

   v15.clear();

   if((v15.size() != 0) || (v15.capacity() != 60)){
      score[11] -= 5;
      cout << "\nCLEAR ERROR! -5" << endl;
   }
   else{
      cout << "\nCLEAR = OK!" << endl;
   }

   //////////////////////////////////////////////////////////////////


   /////////////////////////////assign///////////////////////////////

   IntVector v16(5, 10);
   score[12] = 5;//score for assign

   v16.assign(7, 8);

   if((v16.size() != 7) || (v16.capacity() != 10) || (v16.at(2) != 8)){
      score[12] -= 5;
      cout << "\nASSIGN ERROR! -5" << endl;
   }
   else{
      cout << "\nASSIGN = OK!" << endl;
   }

   //////////////////////////////////////////////////////////////////


   ////////////////////at + front + back mutators////////////////////

   IntVector v17(5, 0);
   score[13] = 5; //at
   score[14] = 5; //front
   score[15] = 5; // back

   v17.at(2) = 100;
   v17.front() = 48;
   v17.back() = 84;

   if(v17.at(0) != 48){
      score[14] -= 5;
      cout << "\nFRONT ERROR! -5" << endl;
   }
   else{
      cout << "\nFRONT = OK!" << endl;
   }

   if(v17.at(4) != 84){
      score[14] -= 5;
      cout << "\nBACK ERROR! -5" << endl;
   }
   else{
      cout << "\nBACK = OK!" << endl;
   }

   if(v17.at(2) != 100){
      score[14] -= 5;
      cout << "\nMutator AT ERROR! -5" << endl;
   }
   else{
      cout << "\nAT = OK!" << endl;
   }

   ///////////////////////////////////////////////////////////

   //calculating score
   double total = 0;

   for (int i = 0; i < NUM_TESTS; i++){
      total += score[i];
   }
   cout << "\n\nTotal Score: " << total << endl << endl; //out of 100

   return 0;
}
