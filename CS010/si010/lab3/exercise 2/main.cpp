#include <iostream> 
#include <string> 
#include <iomanip> 
using namespace std;
int main() 
{
    string phrase ;
    cout << "Enter a three word phrase: " ;
    getline (cin, phrase) ;
    cout << phrase.substr(0,phrase.find(" ")) << endl ;
    string phrase2 = phrase.substr(phrase.find(" ")+1) ;
    cout << phrase2.substr(0,phrase2.find(" ")) << endl;
    string phrase3 = phrase2.substr(phrase2.find(" ")+1) ;
    cout << phrase3 ;
    return 0;
}
