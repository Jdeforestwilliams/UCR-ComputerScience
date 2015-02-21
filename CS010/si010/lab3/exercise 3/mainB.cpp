#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    int x=1 ;
    if (x==1)
        ++x;
    if (x==2)
        ++x;
    if (x==3)
        ++x ;
    cout << x << endl;
    return 0;
}

//output is 4
