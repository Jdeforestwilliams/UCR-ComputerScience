#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
int main()
{
    int number;
    cout << "Please input a number: ";
    cin >> number;
    if (0 == number % 2){
            cout << "The number you have input is even.";
        }
    if (0 != number % 2){
            cout << "The number you have input is odd.";
        }
return 0;
}
