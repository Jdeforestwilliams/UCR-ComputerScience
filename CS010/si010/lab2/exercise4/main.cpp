#include <iostream> 
using namespace std;
int main ()
{
    int num0 ;
    cout << "Please enter a five digit number " ;
    cin >> num0 ;
    cout << num0 /10000 << endl ;
    cout << (num0 %10000)/1000<< endl ;
    cout << (num0 %1000)/100 << endl ;
    cout << (num0 %100)/10 << endl ;
    cout << (num0%10) << endl ;
    return 0;
}
