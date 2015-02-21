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
// Assignment: <Programming Assignment 8>
//
// I hereby certify that the code in this file
// is ENTIRELY my own original work.
//
// ===========================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;
void draw_picture();
void monster_closet(int &a, int &b, string s);
void genie_closet(int &a, int &b);
void picture_closet();
int main()
{
    srand(1000); 
    string name;
    string monster; 
    int bananas = 5;
    int oranges = 3;
    int sentinel = 0; 
    cout << "Please enter your name: ";
    cin >> name; 
    cout << endl << "Name your scariest monster: "; 
    cin >> monster ;
    cout << endl; 
    char direction;
    
    do
    {
        
        cout << name << ", you are in a room with 4 doors." << endl;
        cout << "You are carrying " << bananas << " bananas and " 
             << oranges << " oranges." << endl << endl;
        cout << "Pick a door to open by typing the direction it is in" <<
                "(N/E/S/W): " ; 
        cin >> direction; 
        cout << endl; 
        
        while (direction != 'N' && direction != 'E' && direction != 'S' && 
            direction != 'W')
            {
                cout << "Pick a door to open by typing the direction it is in" <<
                "(N/E/S/W): " ;
                cin >> direction; 
                cout << endl; 
            }
       int alignment =  rand() % 2;
        if (alignment == 0)
        {
            if (direction == 'N')
            {
                monster_closet(bananas, oranges, monster);
            }
            else if (direction == 'E')
            {
                genie_closet(bananas, oranges);
            }
            else if (direction == 'S')
            {
                picture_closet(); 
            }
            else if (direction == 'W')
            {
                    int score = bananas + oranges; 
                    cout << "You found the exit!" << endl;
                    cout << "Your score is " << score << "(" << bananas <<
                            " bananas and " << oranges << " oranges)." << endl;
                    cout << "Bye bye!!!"<< endl; 
                    sentinel++; 
    
            }
        }
        else if (alignment == 1)
        {
            if (direction == 'N')
            {                
                int score = bananas + oranges; 
                cout << "You found the exit!" << endl;
                cout << "Your score is " << score << "(" << bananas <<
                        " bananas and " << oranges << " oranges)." << endl;
                cout << "Bye bye!!!"<< endl; 
                sentinel++; 
                
            }
            else if (direction == 'E')
            {
                monster_closet(bananas, oranges, monster);
                
            }
            else if (direction == 'S')
            {
                genie_closet(bananas, oranges); 
            }
            else if (direction == 'W')
            {
                picture_closet();
            }
        }
     }while (sentinel == 0);
    return 0; 
    
}
void monster_closet(int &a, int &b, string s)
{
    cout << "WATCH OUT!!" << endl << s << " attacks you and steals all"
            << " of your bananas and oranges."  << endl << endl  ;
     a -= a;
     b -= b; 
}
void genie_closet(int &a, int &b)
{
    cout << "!!POOF!!" << endl;
    cout << "A genie pops out and grants you 2 bananas and 1 orange.";
    cout << endl << endl; 
    a += 2;
    b +=1;
}
void picture_closet()
{
    cout << "You found a picture!"<< endl; 
    draw_picture(); 
    }
void draw_picture()
{
    cout << "********" << endl;
    cout << "*      *" << endl;
    cout << "* -  - *" << endl;
    cout << "*  \\/  *" << endl;
    cout << "*  --  *" << endl;
    cout << "* /  \\ *" << endl;
    cout << "********" << endl;
    cout << endl;
}

