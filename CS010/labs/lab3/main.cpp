#include <iostream>
#include <string>
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
    cout << first_name.substr(0,1) << middle_initial.substr(0,1)
        << last_name.substr(0,1) << last_name.length() << endl ;
    cout << first_name << last_name.substr(0,1)<<first_name.length()<<endl;
    cout << first_name.substr(0,1) << last_name << first_name.length() +
        last_name.length() ;
    return 0 ;
}
    
