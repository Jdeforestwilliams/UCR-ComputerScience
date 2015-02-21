#include <iostream>

using namespace std;

int main ()

{
    double test1 ;
    double test2 ;
    double test3 ;
    double amt_tsts = 3 ;
    cout << "Please enter your three tests scores ( # # # ): " ;
    cin  >> test1 >> test2 >> test3 ;
    cout << "Your average test score is " << (test1 + test2 + test3)/
        amt_tsts << "." << endl;
    
    
    
    return 0;
}
