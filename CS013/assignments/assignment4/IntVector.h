// Course: CS 13 <quarter & year>
//
// First Name: Joshua 
// Last Name: DeForest-Williams
// Course username: <jdefo002>
// email address: <jdefo002@ucr.edu>
//
// Lecture Section: <001>
// Lab Section: <022>
// TA: Byung Hyung Kim 
//
// Assignment: <Assignment 4>
//
// I hereby certify that the code in this file
// is ENTIRELY my own original work.
//
// =================================================================
#include <iostream>
using namespace std;
class IntVector
{
    private:
    
    unsigned int sz;
    unsigned int cap;
    int * data;
    
    public: 
    IntVector();
    IntVector( unsigned int size );
    IntVector( unsigned int size, int value );
    ~IntVector();
    unsigned int size( ) const;
    unsigned int capacity( ) const;
    bool empty( ) const;
    const int &at( unsigned int index ) const;
    const int &front( ) const;
    const int &back( ) const;

};
