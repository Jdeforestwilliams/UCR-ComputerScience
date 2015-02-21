#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
using namespace std;
int main() 
{
    srand(time(NULL));
    const int high = 100 ;
    const int low = 1 ;
    string answer ;
    do {
        int r =  low + rand() % (high - low + 1) ;
        if ( r > 50){
            cout << "Heads" << endl;
        }
        else{
            cout << "Tails" << endl;
            cout << "Would you like to play again? " ;
            cin >>  answer ;
        }
            
    }
    while (answer != "no");
    return 0;
}
