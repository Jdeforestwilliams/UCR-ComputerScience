#ifndef __PET_H__
#define __PET_H__
#include <iostream>
#include <string>
using namespace std; 
class Pet 
{
    private: 
    string name; 
    int age; 
    double weight; 
    public:  
    Pet(string name, int age, double weight);
    string get_life_span()const ; 
    string get_name()const ;
    int get_age()const ;
    double  get_weight()const ;
    void print_info() const;
    void change_weight(double);
    void change_age(int); 
    void change_name(string); 
};
#endif
