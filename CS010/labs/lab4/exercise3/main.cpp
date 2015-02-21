#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
int main()
{
    int first_int ;
    int second_int ;
    cout << "Please enter an integer: ";
    cin  >> first_int ; 
    cout << "Please enter another integer: " ;
    cin  >> second_int ;
    while (second_int < first_int){ 
          cout << "You made an error, please enter another integer: " ;
          cin >> second_int ; 
        }
    int sum = 0;
    for (int i = first_int ; i <=second_int;i++){
            sum = sum+i ;
        }
    cout << "The sum of all integers from " << first_int << " to "
         << second_int << " is " << sum ;
    return 0;
}
