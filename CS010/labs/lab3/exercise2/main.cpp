#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main ()
{
    string first_name ;
    string middle_initial ;
    string last_name ;
    cout << "Enter your first name: " ;
    cin >> first_name ;
    cout << "Enter your middle initial: " ;
    cin >> middle_initial ;
    cout << "Enter your last name: " ;
    cin >> last_name ;
    cout << "Here are some suggestions for email addresses: " << endl ;
    //f = first
    //l = last
    //le = letter
    //m = middle initial
    string flef_last = first_name.substr(0,1) + last_name;
    string first_lle =  first_name + last_name.substr(0,1) ;
    string intials = first_name.substr(0,1) + middle_initial +  
        last_name.substr(0,1) ;
    string first_ml = first_name + middle_initial + last_name.substr(0,1) ;
    string fle_m_last = first_name.substr(0,1) + middle_initial + last_name ;
    string first_last = first_name + "." + last_name;
    cout << setw(20)<< left << flef_last;
    cout << setw(20)<< left << first_lle ;
    cout << setw(20)<< left << intials << endl;
    cout << setw(20)<< left << first_ml ;
    cout << setw(20)<< left << fle_m_last; 
    cout << setw(20)<< left << first_last << endl;
    return 0 ;
}
    
