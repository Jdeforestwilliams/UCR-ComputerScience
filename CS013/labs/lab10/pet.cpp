
#include "pet.h"
#include <iostream> 
using namespace std;
Pet:: Pet(string name, int age, double weight)
:name(name), age(age), weight(weight) 
{}
string Pet::  get_life_span()const 
{  
    string a = "unknown lifespan";
    return a;
}
string Pet::  get_name()const 
{
    return name; 
}
int Pet:: get_age()const
{
    return age; 
}
double Pet::  get_weight()const 
{
    return weight; 
}
void Pet:: print_info() const
{
    cout << "Name: " << name << endl;
    cout << "Age : " << age << endl; 
    cout << "Weight: " << weight << endl; 
}
void Pet:: change_weight(double w)
{
   weight = w; 
}

void Pet:: change_age(int a)
{
    age = a;
}

void Pet::change_name(string n)
{
    name = n; 
}

