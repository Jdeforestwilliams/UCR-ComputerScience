#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector <string> v;
    string word_input; 
    string letter_chosen;
    cout << "Enter words (enter the word done to quit): " << endl; 
    cin >> word_input; 
    v.push_back(word_input); 
    while (word_input != "done") 
    {
        cin >> word_input; 
        v.push_back(word_input); 
        if (word_input.find("done") != -1)
        v.pop_back();
    }  
        cout << endl; 
        cout << "Please enter a letter: " ; 
        cin >> letter_chosen; 
        for (int i = v.size() -1 ; i >= 0; i--)
        {
            if (v.at(i).substr(0,1) == letter_chosen)
            {
                cout << v.at(i);
                cout << endl;
            }
        }
        
    return 0;
}
