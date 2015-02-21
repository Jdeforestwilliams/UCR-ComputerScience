// Course: CS 10 <Winter 2012>
//
// First Name: Joshua
// Last Name: DeForest-Williams
// Login id: <jdefo002>
// email address: <jdefo002@student.ucr.edu>
//
// Lecture Section: <001>
// Lab Section: <e.g. 024>
// TA: Ting-Kai Huang
//
// Assignment: <Programming Assignment 2>
//
// I hereby certify that the code in this file
// is ENTIRELY my own original work.
//
// =======================================================
#include <iostream>
#include <string>
using namespace std;
int main ()
{
    string name1 ;
    string name2 ;
    string name3 ;
    string name4 ;
    string name5 ;
    string name6 ;
    string name7 ;
    string name8 ;
    string name9 ;
    string name10 ;
    int amt_of_times;
    cout << "Please enter in a last name: " ;
    cin  >> name1 ;
    cout << "Please enter in a silly word: " ;
    cin  >> name2;
    cout << "Please enter in a thing: " ;
    cin  >> name3 ;
    cout << "Please enter in an animal: " ;
    cin  >> name4 ;
    cout << "Please enter in a TV show: " ;
    cin  >> name5 ;
    cout << "Please enter in a type of game: " ;
    cin  >> name6 ;
    cout << "Please enter in an adjective ending in -y : " ;
    cin  >> name7 ;
    cout << "Please enter in a pet's name: " ;
    cin  >> name8 ;
    cout << "Please enter in an adjective: " ;
    cin  >> name9 ;
    cout << "Please enter in a verb ending in -ing: " ;
    cin  >> name10 ;
    cout << "Please enter in a whole number: ";
    cin  >> amt_of_times ;
    cout << " Dear Professor " << name1 << ":" << endl ;
    cout << "    My name is " << name2 <<
        " and I am unable to turn in my " << name3 << "." << endl ;
    cout << " I realize you "
        "have probably heard every excuse, but this "
        "time is different." << endl ;
    cout << " My " << name4 << " really did eat it!" << endl ;
    cout << " " << endl ;
    cout << "   I tried to start over, but " << name5 <<
        " came on and I just had to watch!" << endl ;
    cout << " Once it was over, I was going to start working again." << endl ;
    cout << " That was the plan anyway, except"
        " my friends came over and wanted to play "<< endl;
    cout << name6 << " games." << endl;
    cout << " " << endl ;
    cout << "   I know it was " << name7 << " of me to play." << endl;
    cout << "For that, " << name8 << " (the " << name4 <<") and I would like"
        " to apologize." << endl ;
    cout << "We were being " << name9 << " even though that is no excuse,"
        " we still hope you can"<< endl;
    cout << " accept our deepest apologies." ;
    cout << " Thank you for " << name10 << ". We hope to not let this " << endl ;
    cout << "happen " << amt_of_times << " more times." << endl;
    return 0;
}
