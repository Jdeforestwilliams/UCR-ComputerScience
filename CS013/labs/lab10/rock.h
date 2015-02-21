#ifndef __ROCK_H__
#define __ROCK_H__
#include "pet.h"
#include <iostream>
#include <string> 
 
using namespace std; 
class Rock : public Pet
{
    public:
    Rock ( string, int, double); 
    string get_life_span() const;
    void print_info() const; 
    void change_name(string);
    void change_age(int);
    void change_weight(double); 


};

#endif
