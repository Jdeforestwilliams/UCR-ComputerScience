#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
int main() 
{
    int left_operand ;
    int right_operand ;
    int  guess ;
    string operate ;
    string junk ;
    int problem = 1;
    int right = 0;
    while (cin >> left_operand >> operate >> right_operand >> junk >> guess)
       {
            cout <<"Problem number: "<< problem++ << ") " ;
            cout << left_operand << " ";
            cout << operate << " ";
            cout << right_operand << " ";
            cout << junk << " ";
            cout << guess;
            if (left_operand + right_operand == guess)
            {
                cout << " Correct!" << endl;
                right++;
            }
            else if (left_operand - right_operand == guess)
            {
                cout << " Correct!" << endl;
                right++;
            }
            else if (left_operand * right_operand == guess)
            {
                cout << " Correct!" << endl;
                right++;
            }
            else if (left_operand / right_operand == guess)
            {
                cout << " Correct!" << endl;
                right++;
            }
            else if (left_operand % right_operand == guess)
            {
                cout << " Correct!" << endl;
                right++;
            }
            else
            {  
                cout << " Incorrect!" << endl;
            }
        }
    int incorrect = problem - right ;
    cout << "You got " << right << " problems correct and " << 
        incorrect << " problems inccorect." << endl;
    return 0;
}
