// Course: CS 10 <Winter 2012>
//
// First Name:Joshua    
// Last Name:DeForest-Williams
// Login id: <jdefo002>
// email address: <jdefo002@ucr.edu>
//
// Lecture Section: <003>
// Lab Section: <024>
// TA:
//
// Assignment: <Programming Assignment 7>
//
// I hereby certify that the code in this file
// is ENTIRELY my own original work.
//
// ===========================================================
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
int compute_checksum(int number)
{
    int first_num = number / 100000000;
    int second_num = (number % 100000000 / 10000000) * 2;
    int third_num = (number % 100000000 % 10000000 / 1000000)*3;
    int fourth_num = (number % 100000000 % 10000000 % 1000000 / 100000) *4;
    int fifth_num = (number % 100000000 % 10000000 % 1000000 % 100000 
        /10000) *5;
    int sixth_num = (number % 100000000 % 10000000 % 1000000 % 100000 
        %10000 / 1000) *6 ;
    int seventh_num = (number % 100000000 % 10000000 % 1000000 % 100000 
        %10000 % 1000 / 100) *7; 
    int eighth_num = (number % 100000000 % 10000000 % 1000000 % 100000 
        %10000 % 1000 % 100 / 10) *8;
    int ninth_num = (number % 100000000 % 10000000 % 1000000 % 100000 
        %10000 % 1000 % 100 % 10) *9; 
    int isbn = (first_num + second_num + third_num + fourth_num + fifth_num +
                sixth_num + seventh_num + eighth_num + ninth_num) % 11; 
    if (isbn <= 10) 
        {   
            return isbn;
        }
    else 
        {
            cout << "X";
            return 0;
        }
 }  

int main()
 { 
	int number;
	while (cin >> number) 
    {
    cout <<compute_checksum(number) << "\n";
    }
    return 0; 
}
