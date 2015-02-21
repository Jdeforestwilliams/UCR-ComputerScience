// Course: CS 10 <Winter 2012>
//
// First Name: Joshua
// Last Name: DeForest-Williams
// Course username: <jdefo002>
// email address: <jdefo002@ucr.edu>
//
// Lecture Section: <001>
// Lab Section: <024>
// TA:
//
// Assignment: <Programming Assignment 3>
//
// I hereby certify that the code in this file
// is ENTIRELY my own original work.
//
// =================================================================
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main ()
{
    string name;
    double january;
    double february;
    double march ;
    cout<<"Enter person's name (last,first): ";
    cin >> name;
    cout<<"Enter January income: ";
    cin >> january;
    cout << "Enter February income: " ;
    cin >> february ;
    cout << "Enter March income: ";
    cin >> march ;
    cout << endl ;
    double gross_income = january + february + march ;
    double income_tax = gross_income * 0.15 ;
    double net = gross_income - income_tax ;
    cout << "Quarterly statement of earnings" <<endl;
    cout << endl;
    cout << "First Name: " << name.substr( name.find (',') + 1 ) ;
    cout << right << setw(25) <<" Last name: "
        << name.substr(0,name.find(',')) << endl;
    cout << setfill('=');
    cout << setw(75) << "" << endl ;
    cout << setfill (' ');
    cout << left << setw(25) << "January income" ;
    cout << left << setw(25) << "February income" ;
    cout << left << setw(25) << "March income" << endl;
    cout << left << setw(25) << january;
    cout << left << setw(25) << february;
    cout << left << setw(25) << march << endl;
    cout << setfill ('=') ;
    cout << setw(75) << "" << endl ;
    cout << setfill (' ');
    cout << setw(25) << "Total gross income" ;
    cout << setw(25) << "Income Tax" ;
    cout << setw(25) << "Total net income" << endl;
    cout << fixed << setprecision(2) << setw(25) << gross_income ;
    cout << fixed << setprecision(2) << setw(25) << income_tax ;
    cout << fixed << setprecision(2) << setw(25) << net ;
    return 0;

}
