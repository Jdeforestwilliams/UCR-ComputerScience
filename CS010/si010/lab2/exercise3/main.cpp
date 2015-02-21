#include <iostream>
using namespace std;
int main ()
{
    double int_pos ;
    // initial position, Xi
    double int_vel ;
    // initial velocity, Vi
    double acc ;
    //acceleration, a
    double time ;
    // time, t
    cout << "Please enter your intial position: " ;
    cin >> int_pos ;
    cout << "Please enter your intial velocity: ";
    cin >> int_vel ;
    cout << "Please enter your acceleration: " ;
    cin >> acc ;
    cout << "Please enter your time: " ;
    cin >> time ;
    cout << "The final position is " << int_pos + (int_vel * time) + 
        (0.5*(acc*(time*time))) << "." << endl ;
    return 0;
}
