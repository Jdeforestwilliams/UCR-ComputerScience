   #include <iostream>
   #include "assn4.h"
   #include <string>
   using namespace std;
   int main()
   {

        string word = "regal";
        string ch = word.substr(1);
        cout << ch;
        if (is_vowel(ch))
        {
            cout << " is a vowel." << endl;
        }
        else
        {
            cout << " is not a vowel." << endl;
        }
   }
