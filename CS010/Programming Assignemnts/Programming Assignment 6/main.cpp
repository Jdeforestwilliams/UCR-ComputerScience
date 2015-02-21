// Course: CS 10 <quarter & year>
//
// First Name: Joshua
// Last Name: DeForest-Williams
// Course username: <jdefo002>
// email address: <jdefo002@student.ucr.edu>
//
// Lecture Section: <003>
// Lab Section: <024>
// TA:
//
// Assignment: <Programming Assignment 6>
//
// I hereby certify that the code in this file
// is ENTIRELY my own original work.
//
// =================================================================
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
/**
    Puts dashes in place of alpha characters in unsolved phrase.
    @param phrase the phrase to be solved
    @return the phrase with all alpha characters converted to dashes
*/
string setup_unsolved(string phrase)
{
    cout << setfill('-');
    cout << setw(phrase.length() -1 ) << "-";
    return "-";
}

bool valid_char(char check)
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

/**
   Gets valid guesses only. A valid guess is a single alphabetic character
   that has not already been guessed.
   @param guessed the string containing all characters guessed so far.
   @return a valid character entered by user.
 */
string get_guess (valid_char(check))
{
	cout << guessed;
    char check;
	cin >> check;
	while (!valid_char(check))
	{
		cin.clear();
		cout << "Input Error: "
			<< prompt;
		cin.ignore(256,'\n');
		// empty the buffer for the next 256 characters or up to the first new line
		cin >> n;
        guessed = check + guessed;
	}
	cout << "you have guessed: " ;
	return guessed;
}

int main()
{
     string  phrase ;
     char check;
     string prompt = "Please enter in a character: ";
     string guessed;
     getline (cin, phrase);
     cout << setup_unsolved( phrase ) ;
     return 0;

}






