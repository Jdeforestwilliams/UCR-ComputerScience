#include <iostream>
#include <iomanip> 
using namespace std;
int sum(int a,int b)
{
    int sum = 0;
    for (int count = a; count <= b; count++) 
    {
        sum += count;
        
    }
    return sum;
}
int main()
{
    int a , b;
    cout << "Please enter an integer: " ;
    cin >> a;
    cout << "Please enter another integer: ";
    cin >> b;
    cout <<"The total of your two integers is " <<  sum(a,b)<< endl;
    return 0;
}
