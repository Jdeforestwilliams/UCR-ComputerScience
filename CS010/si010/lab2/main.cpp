#include <iostream>

using namespace std;
 
 int main()
 {
     double test1;
     double test2;
     double test3;
     double amt_tsts = 3;
     // finding the average, amount of tests
     cout << "Please enter your first test score " ;
     cin  >>  test1 ;
     cout << "Please enter your second test score " ;
     cin  >> test2 ;
     cout << "Please enter your third test score " ;
     cin  >> test3 ;
     cout << "Your average test score is " << (test1 + test2 + test3)/
        amt_tsts << "." << endl;
    return 0;
}
