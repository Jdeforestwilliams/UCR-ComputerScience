#include <iostream>
using namespace std;

int main()
{
  cout << endl;

  /////// PART 1 ///////////////////////////////////////////

  int * int_ptr1;
  int * int_ptr2;

  int int_var = 100;

  //point int_ptr1 to int_var
    int_ptr1 = &int_var; 

  //allocate memory from the heap (dynamically) and point int_ptr2 at it
  //store the value 200 in this memory
    int_ptr2 = new int (200); 

  cout << "int_var: " << int_var << endl
       << "*int_ptr1: " << *int_ptr1 << endl
       << "*int_ptr2: " << *int_ptr2 << endl
       << endl;

  //add 100 to the values pointed to by both int pointers
 *int_ptr1 += 100; 
 *int_ptr2 += 100; 

  cout << "int_var: " << int_var << endl
       << "*int_ptr1: " << *int_ptr1 << endl
       << "*int_ptr2: " << *int_ptr2 << endl
       << endl;

  //delete all dynamically allocated memory in Part 1
    
  delete int_ptr2;



  /////// PART 2 ///////////////////////////////////////////
  
  //dynamically allocate new memory from the heap for all 3 pointers
  
  int_ptr1 = new int(0);
  int_ptr2 = new int(0);
  int * int_ptr3 = new int(0);

  *int_ptr1 = 400;
  *int_ptr2 = 500;
  *int_ptr3 = 600;

  cout << "int_var: " << int_var << endl
       << "*int_ptr1: " << *int_ptr1 << endl
       << "*int_ptr2: " << *int_ptr2 << endl
       << "*int_ptr3: " << *int_ptr3 << endl
       << endl;

  //point all pointers to the same memory location 
  //  (the one pointed to by int_ptr1)
  //make sure you don't leave allocated memory floating around
  delete int_ptr2;
  delete int_ptr3;
  int_ptr2 = int_ptr1;
  int_ptr3 = int_ptr2;

  cout << "*int_ptr1: " << *int_ptr1 << endl
       << "*int_ptr2: " << *int_ptr2 << endl
       << "*int_ptr3: " << *int_ptr3 << endl
       << endl;
  
  //delete all dynamically allocated memory in part2

  delete int_ptr1;


  return 0;
}
