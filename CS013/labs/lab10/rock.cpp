
#include "pet.h" 
#include "rock.h"
#include <iostream>
#include <string>


using namespace std; 
    Rock :: Rock ( string name, int age, double weight) 
    : Pet(name, age, weight){}
    string Rock::  get_life_span() const
    {
        string a = "Thousands of years";
        return a; 
    }
    void Rock:: print_info() const
    {
        Pet:: print_info(); 
    }

    void Rock:: change_age(int a)
    {
        Pet::change_age(a); 
    }

    void Rock:: change_name(string n)
    {
        Pet::change_name(n); 
    }
    void Rock:: change_weight(double w)
    {
        Pet:: change_weight(w); 
    }
