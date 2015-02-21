// Course: CS 13 <Spring 2012 >
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
// Assignment: <Assignment 5>
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
    int &at( unsigned int index );
    const int &front( ) const;
    int &front( );
    const int &back( ) const;
    int &back( );
    void assign( unsigned int n, int value );
    void push_back( int value );
    void pop_back( );
    void clear( );
    void resize( unsigned int sz );
    void resize( unsigned int sz, int value );
    void reserve( unsigned int n );
    void insert( unsigned int index, int value );
    void erase( unsigned int index );
    
    private: 
    void expand();
    void expand( unsigned int amount );



};
