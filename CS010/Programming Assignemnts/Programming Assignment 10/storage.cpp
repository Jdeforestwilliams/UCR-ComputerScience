#include <vector> 
void get_board(vector<vector<char> > &board) 
{
    vector<char> input; 
    char entry; 
    while(cin >> entry)
    {
        input.push_back(entry); 
    }
    int size = input.size(); 
   for (int i = 0; i <size; i++)
   {
       if (islower(input.at(i)))
       toupper(input.at(i)); 
   }
    for (int i = 0; i<size; i++)
    {
        cout << input.at(i) <,
    }
}

void print_2d(const vector<vector<char> > &board, string delim)
{
    int size = board.size(); 
    for (int row = 0; row < size; row++)
    {
        for (unsigned int col = 0; col <board.at(row).size(); col++)
        {
            cout << board.at(row).at(col) << delim; 
        }
    }
}




search_horizontal(board, words); 


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

    for (int t = 0; t < matched_words.size(); t++)
    {
        cout << matched_words.at(t) << " " ; 
        
    }
}
