#include <iostream> 
#include <iomanip>
using namespace std;
int main()
{
    double purchase_amt ;
    double amt_recieved ;
    cout << "Enter purchase amount: ";
    cin >> purchase_amt ;
    cout << "Enter amount recieved: ";
    cin >> amt_recieved ;
    double change = amt_recieved - purchase_amt ;
    cout << "Total Change: $" << change ;
    cout << " " << endl ;
    int total_change = static_cast <int> (change * 100 +.5) ;
    int dollars = total_change /100 ;
    int quarters  = total_change %100 /25;
    int dimes = total_change %100%25/10;
    int nickels = total_change%100%25%10/5 ;
    int pennies = total_change%100%25%10%5/1 ;
    cout << setw(10) << right << "dollars " << dollars << endl ;
    cout <<setw(10) << right <<  "quarters "<< quarters << endl;
    cout << setw(10) << right << "dimes " << dimes << endl;
    cout << setw(10) << right << "nickels " << nickels << endl ;
    cout << setw(10) << right << "pennies " << pennies << endl;
    return 0;
}
