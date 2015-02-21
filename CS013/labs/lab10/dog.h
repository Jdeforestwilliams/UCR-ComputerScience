#ifndef __DOG_H__
#define __DOG_H__
#include "pet.h"
#include <iostream>
#include <string>

using namespace std;
 
class Dog : public Pet
{
    private: 
    string breed;
    public:
    Dog ( string, int, double, string); 
    string get_breed() const; 
    string get_name() const;
    int get_age() const;
    double get_weight() const;
    string get_life_span() const;
    void print_info() const; 
    void change_weight(double); 
    void change_age(int); 
    void change_name(string);
    void change_breed(string);  
};
#endif
