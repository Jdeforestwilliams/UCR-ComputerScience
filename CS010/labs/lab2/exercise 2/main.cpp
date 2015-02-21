#include <iostream>
using namespace std;
int main()
{
    int age;
    int bpm = 220 ;
    double up_lmt = 0.75 ;
    double lw_lmt = 0.60 ;
    // range limits for bpm
    cout << "Please enter your age ";
    cin  >> age;
    cout << "Your target heart rate is between " << (bpm - age) 
        * lw_lmt << " and " << (bpm - age) * up_lmt << " bpm." << endl ;
    // bpm forumla
    return 0;
}
