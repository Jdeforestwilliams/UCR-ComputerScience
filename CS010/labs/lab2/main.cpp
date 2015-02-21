#include <iostream>
using namespace std;
int main()
{
    int first_int;
    int second_int;
    cout << "Please enter your first integer ";
    // to provide first integer
    cin  >> first_int;
    cout << "please enter your second integer ";
    // to provide second integer
    cin  >> second_int; 
    // finding the sum product or quotient
    cout << first_int << " + " << second_int << " = " << first_int + second_int << endl ;
    cout << first_int << " * " << second_int << " = " << first_int * second_int << endl ;
    cout << first_int << " / " << second_int << " = " << first_int / second_int  << endl ;
    return 0;
}
