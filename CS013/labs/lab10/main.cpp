#include <iostream>
#include "pet.h"
#include "dog.h"
#include "rock.h"
#include <string>
using namespace std;
int main()
{
    Pet p1("Nick", 2,10);
    p1.print_info();
    cout << flush;
    p1.change_age(5);
    p1.print_info();
    cout << flush;
    p1.change_name("Wally");
    p1.print_info();
    cout << flush;
    p1.change_weight(100);
    p1.print_info();
    cout << flush;
    cout << p1.get_life_span()<< endl ;
    
    cout << endl; 
    Rock r1("Nick", 10,100);
    r1.print_info();
    cout << flush;
    r1.change_age(100);
    r1.print_info();
    cout <<  flush;
    r1.change_name("Carlos");
    r1.print_info();
    cout << flush;
    r1.change_weight(5);
    r1.print_info();
    cout << flush;
    cout<<r1.get_life_span()<<endl ;
    
    cout << endl; 
    Dog d1("Steven",5,110, "Aussie"); 
    d1.print_info();
    cout << flush; 
    d1.change_name("Dog");
    d1.print_info();
    cout << flush; 
    d1.change_age(3); 
    d1.print_info();
    cout << flush; 
    d1.change_weight(100); 
    d1.print_info();
    cout << flush; 
    d1.change_breed("Shepard"); 
    d1.print_info();
    cout << flush;
    cout << d1.get_life_span()<<endl ;
    return 0; 
}
