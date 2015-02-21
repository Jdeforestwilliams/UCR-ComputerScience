#include "Date.h"
#include <iostream> 
#include <string>
using namespace std;
    Date ::Date()
    {
        month = 1;
        day = 1;
        year = 1900;
        Month = "January";
        
    }
    Date:: Date( int m, int d, int y)
    : month(m), day(d), year(y)
    {
        Month = name(m);
    }
   Date:: Date (string m, int d, int y)
    :day(d), year(y),Month(m)
    {
       month = number(m); 
    }
    void Date:: print_alpha()
    {
        cout << Month << " " << day << ", " << year << endl;
    }
    void Date :: print_numeric()
    {
        cout << month << " - " << day << " - " << year << endl; 
    }
    string Date:: name (int m)
    {
        string Month; 
        switch(m)      
        {
            case 1: Month = "January";
                break;
            case 2: Month = "February";
                break;
            case 3: Month = "March";
                break;
            case 4: Month = "April";
                break;
            case 5: Month = "May";
                break;
            case 6: Month = "June";
                break;
            case 7: Month = "July";
                break;
            case 8: Month = "August";
                break;
            case 9: Month = "September";
                break;
            case 10: Month = "October";
                break;
            case 11: Month = "November";
                break;
            case 12: Month = "December";
                break;
        }
    return Month; 
    }
    int Date :: number (const string &m)
    {       
            int mon; 
            if (m == "January") {mon = 1; return mon;}
            else if (m == "February") {mon = 2;return mon;}
            else if (m == "March"){ mon = 3;return mon;}
            else if (m =="April"){ mon = 4;return mon;}
            else if (m == "May"){ mon = 5;return mon;}
            else if (m =="June"){ mon = 6;return mon;}
            else if (m =="July"){ mon = 7;return mon;}
            else if (m =="August"){ mon = 8;return mon;}
            else if (m =="September"){ mon = 9;return mon;}
            else if (m =="October"){ mon = 10;return mon;}
            else if (m =="November"){ mon = 11;return mon;}
            else if (m =="December"){mon =12;return mon;}
            return mon; 
    }
