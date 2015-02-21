// Course: CS 10 <quarter & year>
//
// First Name: Joshua
// Last Name: DeForest-Williams
// Course username: <jdefo002>
// email address: <jdefo002@ucr.edu>
//
// Lecture Section: <003>
// Lab Section: <024>
// TA: Ting-Kai Huang
//
// Assignment: <assn1, hw2, lab3, etc.>
//
// I hereby certify that the code in this file
// is ENTIRELY my own original work.
//
// =================================================================
#include <iostream>
#include <string>
#include <iomanip>
#include "assn4.h"
using namespace std;
int main()
{
    string word;
    int word_count = 0 ;
    int sentence = 0;
    string period = "." ;
    string exclamation = "!" ;
    string question = "?";
    string comma = "," ;
    string semicolon = ";" ;
    string colon = ":" ;
    int syllable = 0;
     
    while(cin >> word)
        {
            // to count the words for each word entered in
            word_count++ ;
            
            if (word.substr(word.size()-1,1) == period )
                {
                    sentence++ ;
                    // to count the number of sentences ending in a period
                }
            
            else if (word.substr(word.size()-1,1) == exclamation )
                {
                    sentence++ ;
                    // to count the number of sentences ending in an 
                    // exlcamation
                }
                
            else if (word.substr(word.size()-1,1) == question )
                {
                    sentence++ ;
                    // to count the number of sentences ending in a question
                }
                
            else if (word.substr(word.size()-1,1) == semicolon )
                {
                    sentence++ ;
                    // to count the number of sentences ending in a semicolon
                }
                
            else if (word.substr(word.size()-1,1) == colon )
                {
                    sentence++ ;
                    // to count the number of sentences ending a colon
                }
                
            for ( unsigned int ch = 0; ch <= word.size();ch++)
                // to count syllables
                // usigned due to error of comparing between signed and 
                // unsigned integer expressions 
                {
                    if (is_vowel(word.substr(ch,1)))
                    {
                        syllable++ ;
                    }
                }
        }
    double leg_index = 206.835 - 84.6 * ( syllable / word_count) - 
        1.015 * ( word_count / sentence ) ;
    cout << "Word cout: " << word_count << endl;
    cout << "Syllables: " << syllable << endl;
    cout << "Sentence: " << sentence << endl;
    cout << "Legibility Index: " << leg_index << endl; 

    return 0;
}

