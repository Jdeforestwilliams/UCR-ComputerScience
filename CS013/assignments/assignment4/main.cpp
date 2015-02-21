#include <iostream>
#include <string>
#include "IntVector.h"

using namespace std;
int main()
{
    IntVector a;
    IntVector b(5);
    IntVector c(10,8);
    cout << c.at(0) << " " << b.at(0) << "  " <<  a.at(0)<< endl; 
    return 0;
}
