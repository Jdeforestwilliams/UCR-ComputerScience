#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
    int i ;
    for ( i = 0; i <= 24 ; i++)
        {
            cout << i << " ";
        }
    cout << i << endl ;
    cout << endl << endl;
    int j ;
    for ( j = 1 ; j <= 97 ; j +=2)
        {
            cout << j << " " ;
        }
    cout << j <<endl ;
    cout << endl << endl;
    int k ;
    for ( k = 2 ; k <=32 ; k *=-2) 
        {
            cout << k << " " ;
            
        }
    return 0;
}
