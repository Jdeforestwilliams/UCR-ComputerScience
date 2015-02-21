// Course: CS 10 <Winter 2012>
//
// First Name: Joshua   
// Last Name: DeForest-Williams
// Course username: <jdefo002>
// email address: <jdefo002@ucr.edu>
//
// Lecture Section: <003>
// Lab Section: <024>
// TA: Ting-Kai Huang
//
// Assignment: <Programming Assignment 9>
//
// I hereby certify that the code in this file
// is ENTIRELY my own original work.
//
// =================================================================
#include <vector>
#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

/** draw_board
    draws the current tic-tac-toe board to standard output
    @param board is the tic-tac-toe board passed by constant reference
*/
void draw_board(const vector<char> &board)
{
    system("clear");
    cout << endl;
    for (int i=0; i<9; i+=3)
    {
        cout << "  " << board.at(i) << "  |  " << board.at(i+1) << "  |  "
             << board.at(i+2) << "  " << endl;
        if (i < 6)
            cout << "-----|-----|-----" << endl;
    }
    cout << endl;
}

/** valid_placement
    determines if a particular position in the board is available
	@param board is the tic-tac-toe board passed by constant reference
	@param position is a position (square) in the board
	@return true if the position is available (not marked yet), 
	        false if the position already has an X or O
*/
bool valid_placement(const vector<char> &board, int position)
{
  
    if (board.at(position) == 'X'  || board.at(position) == 'O')
    return false;
    else
    return true;
}


/** get_play
    Gets a valid position from the user. Uses valid_placement function.
	@param board is the tic-tac-toe board passed by constant reference
	@return a valid position on the board (one not marked yet)
*/
int get_play(const vector<char> &board)
{
	int position;
    cout << "Please choose a position: "; 
    cin >> position; 
    cout << endl;
    while (valid_placement(board, position-1) == false)
    {
    cout << "Please choose a position: "; 
    cin >> position; 
    cout << endl; 
    }
    
    return position;
}

/** game_won
    Determines whether the game has been won yet
	@param board is the tic-tac-toe board passed by constant reference
	@return true if one of the players has won, otherwise false
*/
bool game_won(const vector<char> &board)
{
    if (board.at(0) == board.at(1) && board.at(1) == board.at(2))
    return true; 
    else if (board.at(3) == board.at(4) && board.at(4) == board.at(5)) 
    return true; 
    else if (board.at(6) == board.at(7) && board.at(7) == board.at(8)) 
    return true; 
    else if (board.at(0) == board.at(3) && board.at(3) == board.at(6)) 
    return true; 
    else if (board.at(1) == board.at(4) && board.at(4) == board.at(7)) 
    return true; 
    else if (board.at(2) == board.at(5) && board.at(5) == board.at(8)) 
    return true; 
    else if (board.at(0) == board.at(4) && board.at(4) == board.at(8)) 
    return true; 
    else if (board.at(2) == board.at(4) && board.at(4) == board.at(6)) 
    return true; 
    return false;
}

/** tie_game
    Determines if there is a tie game. Assumes there is no winner.
	@param board is the tic-tac-toe board passed by constant reference
	@return true of there is a tie game (all positions marked), 
	        false if any position is not marked
*/
bool tie_game(const vector<char> &board)
{
    int i = 0;
    while (i < 9) 
       {
            if(board.at(i) == 'X' || board.at(i) == 'O')
            i++; 
            else 
            return false;
        }
    return true; 
}

const int PLAYER1 = 0;
const int PLAYER2 = 1;

int main()
{
    // use the following variables to store 
	//  - the tic-tac-toe board 
	//  - the current position played
    //  - whose turn it is
    vector<char> board(9);
    int cur_play;
    int turn = PLAYER1;
    
    // Initialize board to empty 
    int size = board.size();
    for(int i= 0; i< size; i++) 
    {
        board.at(i) = '1' + i; 
        }

    // Display empty board
    draw_board(board);
    //repeat until game over
    do
    {
        // Get a play
        cur_play = get_play(board); 
        // Switch play back to zero based position
        cur_play -=1; 
        // Set the play on the board
        if (turn == PLAYER1)
        board.at(cur_play) = 'X';
        if (turn == PLAYER2)
        board.at(cur_play) = 'O';
        // Output the updated board
        draw_board(board); 
        // Switch the turn to the other player
        if (turn == PLAYER1)
        turn = PLAYER2; 
        else if (turn == PLAYER2)
        turn = PLAYER1; 
    }while (tie_game(board) == false && game_won(board) == false); 
    //Output who won
    if (game_won(board) == true && turn == PLAYER1)
    cout << "Player 2 (O's) wins!";
    else if (game_won(board) == true && turn == PLAYER2)
    cout << "Player 1 (X's) wins!";
    else if(tie_game(board) == true)
    cout << "No one wins";
    //Output must be one of these 3 options (exactly like these)
         //"Player 2 (O's) wins!"
         //"Player 1 (X's) wins!"
         //"No one wins"
		 
    return 0;
}
