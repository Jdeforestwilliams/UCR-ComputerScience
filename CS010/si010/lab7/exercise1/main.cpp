#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
string equalizer(string s);
int main()
{
    string return_s;
   
    cout << "Please enter in numbers are your discretion: ";
    cin >> return_s;
    
    equalizer(return_s);
    cout << return_s ;
}
string equalizer( string return_s )
{
    string s = return_s; 
    for ( int i = 0; i <= (int)s.size(); i++)
    {
        
        if ( i == 0)
        {
            if (return_s.at(i+1) > return_s.at(i))
            {
                s.at(i)++; 
            }
            else 
            {
                s.at(i)--;
            
            }
        }
        else if (i == (int)s.size()-1)
        {
            if ( s.at(i) > s.at(i-1) )
            {
                s.at(i)--;
            }
            else 
            {
                ;
            }
            
            }
        else
        {
            if (s.at(i) > s.at(i-1) && (s.at(i) < s.at(i+1))
            {
                s.at(i)
            }
    
    }
}
