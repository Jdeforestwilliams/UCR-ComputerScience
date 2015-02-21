#include <iostream>
#include <string>
using namespace std;

class Date 
{
    private:
    
    int month;
    int day;
    int year;
    string Month;
     
    public:
     
    Date ();
    Date ( int m, int d, int y); 
    Date (string m, int d, int y); 
    void print_alpha();
    void print_numeric();
    
    private:
    
    string name (int m); 
    int number (const string &m);
};
