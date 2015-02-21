#include <iostream>
#include <iomanip>
using namespace std;

int main ()
{
    //a)
    cout << setfill('*');
    cout << left << setw(10) << "Hello" 
        << right << setw(10) << "world!" << endl;
    //b)
    cout << left << setw(10) << "Hello" << endl;
    cout << right << setw(10) << "world!" << endl;
    return 0;
}
