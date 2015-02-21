// Course: CS 10 
//
// First Name: Joshua  
// Last Name: DeForest-Williams
// ILearn username: jdefo002
//
// Lecture Section: 003
// Lab Section: 024
// TA: Ting-Kai Huang
//
// Assignment: Programming Assignment 10
//
// I hereby certify that the code in this file
// is ENTIRELY my own original work.
//
// =====================================================

#include <iostream>
#include <vector> 
#include <iomanip>
#include <string> 
using namespace std;
void get_board(vector<vector<char> > &board); 
void search_horizontal(const vector<vector<char> > &board,
        const vector<vector<char> > &words); 
int main()
{

    vector<vector<char> > board;
    get_board(board); 
   
   
    
    
}
void get_board(vector<vector<char> > &board) 
{

    vector<char> row;
    vector<vector<char> >words; 
    vector<char> letters; 
    string line;
    int size = line.size(); 
    
    getline(cin, line);

   do 
    {
        for (int i = 0; i < size; i++)
        row.push_back(line.at(i));
       
        board.push_back(row);
        row.clear();

        getline(cin, line);
    }while (line.size() != 0);
    if (line.size() == 0)
    getline(cin,line);
    cout << endl;
 
    do 
    {
        for (int j = 0; j < size; j++)
        letters.push_back(line.at(j)); 
        
        words.push_back(letters); 
        getline(cin,line);
    }while (line.size() != 0); 
        
search_horizontal(board, words);

}
 


void search_horizontal(const vector<vector<char> > &board, 
            const vector<vector<char> > &words)
{
    int size = board.size(); 
   vector<char> matched_words; 
    int i = 0;
    int j = 0; 
    while(i < size)
    {
        while(j < size-1)
        {
           if(board.at(i).at(j) == words.at(i).at(j) )
           {
               matched_words.push_back(board.at(i).at(j)); 
               
            }
            else 
           {
               i++;
               j++;
               matched_words.push_back('\n'); 
           }
        }
    }
}
