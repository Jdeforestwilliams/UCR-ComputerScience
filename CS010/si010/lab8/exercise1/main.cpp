#include <iostream> 
#include <vector> 
#include <string> 
#include <iomanip>
#include <cstdlib>
using namespace std;
void output_choices(vector<string>operators, vector<int>operands);
int do_operation(int left, string s, int right);
int main()
{
    int starting_num;
    int k;         
    vector<string> operators;
    vector<int> operands; 
    int size = operators.size()+1;
    cout << "Enter a number you would like to start at from 0 to 50: "; 
    cin >> starting_num;    

    vector<string> operands(4); 
    vector<int> operators(4); 
    operators.at(0) = '+';
    operands.at(0) = 2;
    operators.at(1) = '-';
    operands.at(1) = 8;
    operators.at(2) = '*';
    operands.at(2) = 3;
    operators.at(3) = '+';
    operands.at(3) = 6;
        
    

    output_choices(operators, operands);
    return 0;
}


void output_choices(vector<string> operators, vector<int> operands)
{
    int size = operators.size(); 
    int choice; 
    do  
    {
        for (int i= 0; i <size; i++)
        {
            cout << "Choice "<< i << ": " << operators.at(i) << 
                    operands.at(i);
        }

        
        cout << "Please Pick a Choice (-1 to quit): ";
        cin >> choice; 
        cout << do_operation( 
    }while (choice != -1);
}

int do_operation(int left, string s, int right)
{
    int sum;
    if (s == "+")
    {
       sum = left + right; 
    }
    if (s == "-")
    {
        sum = left - right;
    }
    if (s == "/")
    {
        sum = left/right;
    }
    if (s == "*")
    {
        sum =  left*right; 
    }
    return sum; 
}
    
