#include <iostream> 
using namespace std;
int main ()
{
    double acct_bal ;
    double int_rate ;
    int num_yrs ;
    int percent = 100 ;
    cout << "Please enter your account balance: " ;
    cin >> acct_bal ;
    cout << "Please enter your interest rate: " ;
    cin >> int_rate ;
    cout << "Please enter the number of years: " ;
    cin >> num_yrs ;
    double total = (acct_bal * int_rate * num_yrs)/ percent ;
    cout << " " << endl ;
    cout << "Your interest income after " << num_yrs  
         << " years is $" << total << "." <<endl ; // total interest formula
    return 0;
}
