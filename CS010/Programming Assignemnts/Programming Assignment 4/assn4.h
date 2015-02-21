/* CS 10 Winter 2012
 * Assn 4 Header File
 */

#include <string>

/**
   Determines if a character is a vowel.
   If the string parameter has more than one character, 
   only the first character is looked at.
   @param character the character being examined
   @return true if character is a vowel, false if it isn't
*/ 
bool is_vowel( std::string character )
{
  char ch = tolower(character[0]);
  return ch == 'a' || ch == 'e' || ch == 'i' ||
         ch == 'o' || ch == 'u' || ch == 'y';
}
