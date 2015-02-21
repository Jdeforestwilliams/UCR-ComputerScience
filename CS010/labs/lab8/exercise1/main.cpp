#include <iostream>
#include <iomanip>
#include <string>
using namespace std; 
void draw_square(int);
void draw_up_triangle(int);
void draw_low_triangle(int);

int main()
{   
    int choice;
    do
    {
        
        int length; 
        cout << "1. Print a square." << endl;
        cout << "2. Print upper isosceles triangle." << endl;
        cout << "3. Print lower isosceles triangle." << endl; 
        cout << "4. Exit the program." << endl << endl;
        cout << "Pick a choice (by number) : " ;
        cin  >> choice; 
        cout << endl << endl;
        if (choice == 1)
        {
            cout << "Enter Side Length: " ;
            cin  >> length;
            cout << endl;
            draw_square(length);
        }
        if (choice == 2)
        {
            cout << "Enter Side Length: " ;
            cin  >> length;
            cout << endl;
            draw_up_triangle(length);
        }
        if (choice == 3)
        {
            cout << "Enter Side Length: " ;
            cin  >> length;
            cout << endl;
            draw_low_triangle(length);
        }
        if (choice == 4)
        {
            break;
        }
    }while (choice != 4);
    return 0;
}
 void draw_square(int length)
 {
     for (int i = 0; i < length; i++)
     {
         for (int j = 0; j < length; j++)
         {
             cout << "* ";
        }
        cout << endl;
    }    
     }
 void draw_up_triangle(int length)
 {
     for (int i = 1; i <= length; i++)
     {
        for (int k = 2; k <= i; k++)
        {
            cout << ' ' << ' ' ;
        } 
        
        for (int j = length; j>= i ; j--)
        {
            cout << "* ";
        }
    cout << endl;
    }
 }
 void draw_low_triangle(int length)
 {
     for (int i = 0; i < length; i++)
     {
        for (int j = 0; j <= i; j++)
        {
            cout << "* ";
        }
        cout << endl;
        }
        
 }
