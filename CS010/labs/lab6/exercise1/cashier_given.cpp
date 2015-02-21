/* Exercise 1 of Lab 7
 *
 * Name: 
 * Lab Section:
 * Date: 
 *
 * Implement total and change functions for a vending machine
 * Given: main function to test with
 */
#include <iostream>
#include <iomanip>
using namespace std;
// TODO: declare prototypes of functions for total and change
double total (double price, int quantity)
    {
        double total_price = price * quantity ;
        return total_price;
    }
double change (double price, double payment)
    {
        double change = payment - price;
        return change;
    }
int main()
{
    // Precision constants for decimal values
    const int MONEY = 2;
    // Constant prices
    const double TWINKIE_PRICE = 0.60;
    const double DRPEPPER_PRICE = 1.25;
    const double GUM_PRICE = 0.40;
    // Constant choices
    const int TWINKIE = 1;
    const int DRPEPPER = 2;
    const int GUM = 3;
    // Variables for input
    int choice, quantity;
    double payment;
    // Variables for calculations
    double price;
    double total_price;
    // Output the price list
    cout << "1) Twinkies $0.60\n";
    cout << "2) Dr. Pepper $1.25\n";
    cout << "3) Gum $0.40\n";
    // Ask user what to purchase
    cout << "What would you like to buy? ";
    cin >> choice;
    // Determine price of item based on user input
    if (TWINKIE == choice){
        price = TWINKIE_PRICE;
    }
    else if (DRPEPPER == choice){
        price = DRPEPPER_PRICE;
    }
    else if (GUM == choice){
        price = GUM_PRICE;
    }
    // Acquire quantity of item from the user
    cout << "How many would you like to buy? ";
    cin >> quantity;
    // Determine the total price, calculate with the implemented total function
    total_price = total(price, quantity);
    // Set the precision for decimals to that of monetary values
    cout << fixed << setprecision(MONEY);
    // Output the total price
    cout << "Your total price is $" << total_price << endl;
    // Acquire the monetary amount given to the cashier
    cout << "Enter amount giving cashier: ";
    cin >> payment;
    // Output amount of change, calculate with the implemented change function
    cout << "Your change is $" << change(total_price, payment) << endl;
    return 0;
}


// TODO: Implement total function with proper comments


// TODO: Implement change function with proper comments 

