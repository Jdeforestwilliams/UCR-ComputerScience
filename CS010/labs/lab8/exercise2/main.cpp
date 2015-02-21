#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std; 
int main()
{
    vector<int> numbers(9);
    numbers.at(2) = 1;
    numbers.at(4) = 1;
    numbers.at(5) = 1;
    numbers.at(7) = 1; 
    for (int i = 0; i < 9; i++)
    {
        if (numbers.at(i) ==0)
        {
            cout << "X ";
            if ((i+1)%3 ==0)
            cout << endl;
        } 
        if (numbers.at(i) == 1)
        {
            cout << "O ";
            if ((i+1) % 3 == 0)
            cout << endl;
        }
    }
    return 0;
} 
