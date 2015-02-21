#include <iostream>
#include <iomanip>
using namespace std;
bool valid_char (char check)
{ 
    if ( check >= 'a' && check <= 'z')
    {
        return true;
    }
    else 
    {
        return false;
    }
}
string decrypt (string s)
{
    const int SHIFT = 5;
    for(int i = 0 ; i < s.size();i++)
    {
        if (valid_char (s.at(i)))
        {
          char mychar = s.at(i);
           s.at(i) = 'a' + ((( mychar - 'a') - SHIFT +26) % 26);
        }
    }
    return s;
}

int main()
{
    string s;
    getline (cin,s);
    s = decrypt(s);
    cout << s << endl;
    return 0;
}
