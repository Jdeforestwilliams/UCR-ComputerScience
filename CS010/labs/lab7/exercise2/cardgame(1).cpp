/* Exercise 2 of Lab 7
 *
 * Name:
 * Lab Section:
 * Date: 
 *
 * Create the card game in the lab specification.
 */

#include <iostream>
#include <cstdlib>

using namespace std;


// TODO: declare function prototypes
    string translate_card_num (int number);

    string translate_card_type (int number);
   
    void print_winnings (int one, int two);
    
// TODO: Face card constants
const int ACE = 1;
const int JACK = 11;
const int QUEEN = 12;
const int KING = 13;

// TODO: Suit type constants
const int HEARTS = 1;
const int DIAMONDS = 2;
const int SPADES = 3;
const int CLUBS = 4;
// TODO: Ranges for random, some based on other constants
const int LOW_NUM = 1;
const int HIGH_NUM = 13;
const int LOW_SUIT = 1;
const int HIGH_SUIT = 4;

int main()
{
    
    // Game variables
    srand(time(NULL));

    int first_card_num  = LOW_NUM + rand() % HIGH_NUM; 
    int second_card_num = LOW_NUM + rand() % HIGH_NUM;
    int first_card_type = LOW_SUIT+ rand() % HIGH_SUIT;  
    int second_card_type = LOW_SUIT + rand() % HIGH_SUIT; 
    string card_num, card_type, prize;

    // TODO: Seed the random number generator
    if ( first_card_num > 10 && first_card_num < 14 || first_card_num ==1)
    cout << "You drew a(n) " << translate_card_num( first_card_num) << " of "
        << translate_card_type( first_card_type) << endl;
    else 
    cout << "You drew a(n) " << first_card_num << " of "
        << translate_card_type( first_card_type) << endl;
    
    // TODO: Draw first card by getting a random number / random suit combo
    if (second_card_num > 10 && second_card_num < 14 || second_card_num ==1)
    cout << "You drew a(n) " << translate_card_num(second_card_num) << " of "
        << translate_card_type( second_card_type)  << endl;
    else 
    cout << "You drew a(n) " <<second_card_num << " of "
        << translate_card_type( second_card_type) << endl;
    

    // TODO: do-Keep drawing second card while-it is the same as first
    // HINT: what defines a card to be the same? make conditionals from these



    // TODO: Translate the card number (if needed) into a string using function

    // TODO: Translate the card type into a string using function


    // TODO: Output first card to user
    // HINT: two cases, face card and not


    
    // TODO: Translate the card number (if needed) into a string using function

    // TODO: Translate the card type into a string using function


    // TODO: Output second card to user
    // HINT: two cases, face card and not
     
 
    // TODO: Call function to output winnings
    print_winnings(first_card_num, second_card_num);
 
    return 0;
}


// TODO: create translate_card_type function, takes a suit type number returns
//        a string of the proper suit
// HINT: use your global constants for suit type values

    string translate_card_type (int number) 
    {
        string hearts = "Hearts";
        string diamonds = "Diamonds";
        string spades = "Spades";
        string clubs = "Clubs";
        
        if (number == HEARTS)
        return hearts;
        else if (number == DIAMONDS)
        return diamonds;
        else if (number == SPADES)
        return spades;
        else if (number == CLUBS)
        return clubs;
        else 
        return "";
    } 

// TODO: create translate_card_num function, takes a card number and returns
//       the proper face name string for passed card value
// HINT: use your global constants for face card values
 string translate_card_num (int number)
    {
        string ace = "Ace";
        string jack = "Jack";
        string queen = "Queen";
        string king = "King";
        if (number == ACE) 
        return ace;
        else if (number == JACK)
        return jack;
        else if (number == QUEEN)
        return queen;
        else if (number == KING)
        return king;
        else
        return "";
    }

// TODO: create a print_winnings function to determine what the player wins
//         the function takes the two numerical values of the card and outputs
//         a string stating 'large prize', 'small prize' or 'nothing'
//         this fuction is a void function and returns nothing


void print_winnings(int one, int two)
    {
        if (one == two) 
        cout << "Large Prize!";
        else if (one == JACK) 
        cout << "Small Prize!";
        else if (two == JACK)
        cout << "Small Prize!";
    
        else 
        cout << "Nothing";
    }
