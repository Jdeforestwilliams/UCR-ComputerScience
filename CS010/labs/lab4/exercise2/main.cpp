#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
int main()
{
    int space_entity ;
    int weight ;
    cout << "Would you like to go to the Moon or Mars" << endl ;
    cout << "0 for the Moon, 1 for Mars: " ;
    //the moon is not a planet
    cin  >> space_entity ;
    cout << "Please enter your weight: ";
    cin  >> weight ;
    cout << endl;
    if (1 == space_entity) {
            cout << "Your weight on the planet Mars is: ";
            cout << static_cast <double> (weight * (377.0/1000.0)) ;
        }
    if (0 == space_entity) {
            cout << "Your weight on the Moon is: " ;
            cout << fixed << setprecision(1) 
                <<static_cast <double> (weight * (1.0/6.0)) ;
        }
    return 0 ;
}
