#include <iostream>
#include <iomanip>
using namespace std;

int main ()
{
    string full_name ;
    cout << "Please enter your full name: ";
    getline (cin,full_name) ;
    int size = full_name.size();
    int top = size +2 ;
    int name = full_name.size()+1;
    cout << setfill('*') ;
    cout << setw(top)<< "" << endl ;
    cout << right << setw(1)<< "";
    cout << left << setw(name) << full_name << endl;
    cout << setw(top)<< "" << endl;
    return 0;
}
