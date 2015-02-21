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
#include "IntVector.h"
using namespace std;
    IntVector:: IntVector()
    {
        sz = 0; 
        cap = 0; 
        * data = 0; 
    }
    IntVector:: IntVector( unsigned int size )
    {
        sz = size; 
        cap = size; 
        data = new int [size];
    }
    IntVector:: IntVector( unsigned int size, int value )
    {
        sz = size; 
        cap = size;
        data = new int[size];
        unsigned int i = 0;
        while (i < size)
        {
            data[i] = value; 
            i++;
        }
    }
    IntVector:: ~IntVector()
    {
        delete data; 
    }
    unsigned int IntVector::  size( ) const
    {
        return sz;
        
    }
    unsigned int IntVector:: capacity( ) const
    {
        return cap; 
    }
    bool IntVector:: empty( ) const
    {
        if (sz == 0)
        {
            return true;
        }   
        return false; 
    }
    const int &IntVector::at( unsigned int index ) const
    {
            if (index >= sz)
            {
                exit(0); 
            }
            return *((data + index)-1); 
    }
    const int &IntVector::front( ) const
    {
            if(sz == 0)
                exit(0);
            return *data;
    }
    const int &IntVector::back( ) const
    {
            if (sz == 0)
                exit(0); 
            return *(data +(sz-1));
    }
