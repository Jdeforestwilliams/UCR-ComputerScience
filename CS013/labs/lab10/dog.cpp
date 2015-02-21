#include <iostream>
#include <string> 
#include "dog.h"
#include "pet.h"
using namespace std; 
Dog:: Dog ( string name, int age, double weight, string breed)
:Pet(name, age, weight),breed(breed){}
string Dog:: get_breed() const 
{
    return breed;
}
string Dog:: get_name() const
{
    Pet::get_name();
}
int Dog:: get_age() const
{
    Pet::get_age();  
}
double Dog:: get_weight() const
{
    Pet::get_weight();  
}
string Dog:: get_life_span() const
{
    string a = "Approximately 13 years";
    string b = "Approximately 7 years";
    if  (get_weight() <= 100)
           return a; 
        else
           return b; 
     
}
void Dog:: print_info() const
{
    Pet:: print_info(); 
    cout << "Breed: " << get_breed()<< endl; 
}
void Dog:: change_weight(double w)
{
    Pet::change_weight(w);
}
void Dog:: change_age(int a)
{
    Pet::change_age(a);  
}
void Dog:: change_breed(string b)
{
    breed = b; 
}

void Dog:: change_name(string n)
{
    Pet:: change_name(n);
}
