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
    double zero = 0;
    double twenty = 0;
    double twenty_one = 0;
    double twenty_two = 0;
    double twenty_three = 0;
    double twenty_four = 0;
    double twenty_five = 0;
    double turn = 1;
    srand(1000) ;
    cout << "Hold-at-20 turn simulations? " ;
    cin >> num_turns ;
    do
    {
        int roll = low + rand()%(high - low + 1) ;
        double score = 0 ;
        while (score <= 20 && roll !=1)
            {
                if (roll == 2)
                {
                    score +=2;
                }
                else if (roll == 3)
                {
                    score +=3 ;
                }
                else if (roll == 4)
                {
                    score +=4;
                }
                else if (roll == 5)
                {
                    score +=5;
                }
                else if (roll == 6)
                {
                    score +=6;
                }
            }
            if (roll == 1)
                {
                 zero++;
                }
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
            turn++;
        }  while (turn <= num_turns);
    cout << "Score\tEstimated Probability" << endl;
    cout << "0\t" << zero / num_turns << endl;
    cout << "20\t" << twenty / num_turns << endl;
    cout << "21\t" << twenty_one / num_turns << endl;
    cout << "22\t" << twenty_two / num_turns << endl;
    cout << "23\t" << twenty_three / num_turns << endl;
    cout << "24\t" << twenty_four / num_turns << endl;
    cout << "25\t" << twenty_five / num_turns << endl;
    return 0;
    }
