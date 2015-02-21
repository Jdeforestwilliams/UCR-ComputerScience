#include <iostream>
#include <iomanip>
#include <string>
#include "assn4.h"
using namespace std;
int main()
{
	string word;
	int syllable ;
	int i = word.size() - 1;
	while (cin>>word)
	{
        if (is_vowel(word.substr( i , 1)))
            {
                if (!is_vowel(word.substr(i,1)))
                syllable ++ ;
            }
	}
    cout << "syllable count: " <<  syllable << endl;

	return 0;
}

