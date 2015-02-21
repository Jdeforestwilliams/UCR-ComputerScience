#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
int main ()
{
    string word;
    int word_count = 0 ;
    while(cin >> word)
        {
            word_count = word.size() + word_count ;
        }
    cout << "Character cout: " << word_count ;
}
