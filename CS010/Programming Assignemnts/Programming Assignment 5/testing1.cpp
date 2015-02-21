// Course: CS 10 <quarter & year>
//
// First Name: Joshua
// Last Name: DeForest-Williams
// Login id: <jdefo002>
// email address: <jdefo002@ucr.edu>
//
// Lecture Section: <003>
// Lab Section: <24>
// TA: Ting-Kai Huang
//
// Assignment: <Programming Assignment 5>
//
// I hereby certify that the code in this file
// is ENTIRELY my own original work.
//
// ===========================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
    double num_turns ;
    int high = 6 ;
    int low = 1 ;
    double score = 0 ;
    double one = 0;
    double two = 0;
    double three = 0;
    double four = 0;
    double five = 0;
    double six = 0;
    double zero = 0;
    double twenty = 0;
    double twenty_one = 0;
    double twenty_two = 0;
    double twenty_three = 0;
    double twenty_four = 0;
    double twenty_five = 0;
    srand(1000) ;
    cout << "Hold-at-20 turn simulations? " ;
    cin >> num_turns ;
    for (double turn = 1 ; turn <= num_turns ; turn++)
        {

            do
             {
                int roll = low + rand()%(high - low + 1) ;
                while (score < 20)
                {
                    if (roll == 2)
                    {
                        score +=2;
                    }
                    if (roll == 3)
                    {
                        score +=3 ;
                    }
                    if (roll == 4)
                    {
                        score +=4;
                    }
                    if (roll == 5)
                    {
                        score +=5;
                    }
                    if (roll == 6)
                    {
                        score +=6;
                    }
                }
                while (roll != 1);
               if (score >= 25)
               {
                   twenty_five++;
               }
               else if (score >= 24)
               {
                   twenty_four++;
               }
               else if (score >= 23)
               {
                   twenty_three++;
               }
               else if (score >=22)
               {
                   twenty_two++;
               }
               else if (score >= 21)
               {
                   twenty_one++;
               }
               else if (score >= 20)
               {
                   twenty++;
               }
               if (roll == 1)
                {
                 zero++;
                }
            }
        }
    cout << "zero" << zero << "20" << twenty << "21" << twenty_one << "22"
         << twenty_two << "23" << twenty_three << "24" << twenty_four
         << "25" << twenty_five ;
    return 0;
}
// for probability take the number of how many times you got each score
// divided by the number of turns taken.

