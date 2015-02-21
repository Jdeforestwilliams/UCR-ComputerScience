#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
int main()
{
    int grade ;
    int a = 0 ;
    int b = 0 ;
    int c = 0 ;
    int d = 0 ;
    int f = 0 ;
    do 
    {
        cin >> grade ;
        if (grade >= 90 ) {
            a++;
        }
        else if (grade >= 80){
            b++;
        }
        else if (grade >= 70){
            c++;
        }
        else if (grade >= 60){
            d++;
        }
        else if (grade >= 0) {
            f++;
        }
    }
    while (grade >= 0);
    cout << "You have " << a << " A's, " << b << " B's, " << c << " C's, "
         << d << " D's, and " << f << " F's.";
    return 0;
}

