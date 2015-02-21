#include <iostream>
#include <iomanip>
#include <string>

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
