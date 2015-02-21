#include <iostream> 
#include <iomanip>
using namespace std;
int main ()
 {
     double number ;
     cout << "Enter a floating-point number: ";
     cin >> number ;
     cout << fixed ;
     cout << setw(10) << left << setprecision(0)<< number
        <<setprecision(0)<<number << endl;
     cout << setw(10) << left << setprecision(1)<<number
        <<setprecision(1)<<number <<endl;
     cout << setw(10) << left << setprecision(2)<<number<< 
        setprecision(2)<<number <<endl;
     cout << setw(10) << left << setprecision(3)<<number<< 
        setprecision(3)<<number <<endl;
     cout << setw(10) << left << setprecision(4)<<number<< 
        setprecision(4)<<number <<endl;
     return 0;
 }
