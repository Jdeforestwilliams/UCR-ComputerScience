/* Exercise 1 of Lab 7
 *
 * Name: 
 * Lab Section:
 * Date: 
 *
 * Implement a leap year function that returns whether or not the supplied
 *   year is a valid leap year.
 * For an extra challenge try writing the function as only a return statement
 */

#include <iostream>

using namespace std;

// TODO: Declare prototypes for leap_year function
bool leap_year (int checkYear)
{
    if ( (checkYear % 4 == 0) && (checkYear % 400 == 0) || ( checkYear % 100 
        != 0 ))
    {
       return true;
    }
    else 
    {
        return false;
    }

}


int main()
{
    // Year to check, received via input from user
    int checkYear;


    // Get initial year to check from user
    cout << "What year do you want check (Ctrl+d) to exit)? ";

    // Loop until the sentinel value is entered by user
    while (cin >> checkYear)
    {
        // If the year is a leap year, output that to user
        if (leap_year(checkYear))
        {
            cout << checkYear << " is a leap year!";
        }
        else
        {
            cout << checkYear << " is not a leap year.";
        }
        
        // Get year to check from user again
        cout << endl << endl;
        cout << "What year do you want check (Ctrl+d to exit)? ";
    }

    return 0;
}

// TODO: Implement the leap_year function

