#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<char> v('z' - '!' +1);
    int size = v.size(); 
    char c = '!' ; 
    for (int k = 0; k < size; k++) 
        {
            v.at(k) = c; 
            c++;
        }
    int t = 0;
    while (t < size)    
     {
        for (int i = 0; i < 9; i++)
         {
            for (int j = 0; j < 10; j++)
            {
                cout << v.at(t)<< " "; 
                t++; 
            }
            cout << endl;
        }    
    }
    
    return 0;
}
