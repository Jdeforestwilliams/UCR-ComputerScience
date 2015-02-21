// Course: CS 13 <Spring 2012>
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
#include "IntVector.h"
using namespace std;
    IntVector:: IntVector()
    {
        sz = 0; 
        cap = 0; 
        data = NULL; 
    }
    IntVector:: IntVector( unsigned int size )
    {
        sz = size; 
        cap = size; 
        data = new int [size];
        for (unsigned int i = 0; i < sz; i++)
        {
                data[i]= 0; 
        }
    }
    IntVector:: IntVector( unsigned int size, int value )
    {
        sz = size; 
        cap = size;
        data = new int[size];
        for (unsigned int i = 0; i < size; i++) 
        {
            data[i] = value;
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
            return true ;
        }   
        return false; 
    }
    const int &IntVector::at( unsigned int index ) const
    {
            
        if (index >= sz)
        {
            exit(0); 
        }
        return *(data + index); 
    }
    const int &IntVector::front( ) const
    {
        if(sz == 0)
            exit(0);
        return *data;
    }
    const int &IntVector::back( ) const
    {
        int value; 
        if (sz ==0)
            exit(0); 
        value = sz-1; 
        return *(data+value); 
    }   
    void IntVector:: expand()
    {      
            if (cap == 0)
                cap = 1; 
            cap = cap*2; 
            int * ptr = new int[sz]; 
            for (unsigned int i = 0; i < sz; i++)
            {
                ptr[i] = data[i]; 
            } 
            delete data; 
            data = new int [cap];
            for(unsigned int i = 0; i < sz; i++)
            {
                 data[i]=ptr[i]; 
            }
            delete ptr; 
            if (sz == 0) cap =1; 
    }
    void IntVector:: expand( unsigned int amount )
    {
            cap += amount; 
            int * ptr = new int[sz]; 
            for(unsigned int i = 0; i < sz; i++)
            {
                ptr[i] = data[i];

            }

            delete data;
            data = new int [cap];
            for(unsigned int i = 0; i < sz; i++)
            {
                 data[i]=ptr[i];

            }
            delete ptr;
             
    }
    void IntVector:: insert( unsigned int index, int value )
    { 
        

        if (cap < sz+1)   
            expand();
            sz = sz+1;      
 
        for (unsigned int i = sz-1; i > index; i--)
            data[i] = data[i-1]; 
        data[index] = value; 
    }
    void IntVector:: erase( unsigned int index )
    {
        if ( index >= sz)
            exit(0); 
        for (unsigned int i = index; i < sz-1; i++)
            data[i] = data[i+1]; 
        sz = sz-1;
    }
    void IntVector:: push_back( int value )
    {
        if (sz>= cap)
            expand();
        sz++;
        data[sz-1] = value; 
    }
    void IntVector:: pop_back( )
    {
        if (sz == 0)
            exit(0); 
        sz = sz-1; 
    }
    void IntVector:: clear( )
    {
        sz = 0; 
    }
    void IntVector:: resize( unsigned int size )
    {
        int temp = sz;
 
        if (size < sz)
            sz = size; 
        else if (size > sz && size > cap) 
            {
                if (size - cap > cap *2)
                {  
                    expand(size - cap);
                    sz = size; 
                }
                else if( size - cap < cap *2)
                {
 
                    expand(); 
                    sz = size; 
                }
            }
        else if (size > sz && size < cap)
        {
            sz= size; 
        }
        for (unsigned int i = temp; i < sz; i++)
        {
            data[i] = 0; 
 
        }
        
    }
    void IntVector:: resize( unsigned int size, int value )
    {
     
        if (size > cap) 
            {
                if (size> cap *2)
                {
                    expand(size-cap);
                    
                }
                else 
                {
                    expand(); 
                     
                }
            }
            if (size > sz)
            {
                   int temp = sz;
                   sz = size;
                for (unsigned int i = temp; i < sz; i++)
            {
                data[i] = value; 
               
            }
            }
            else 
            {
                sz = size;
            } 
    }
    void IntVector:: reserve( unsigned int n )
    { 
        if (n > cap)
        {
            if (cap*2<n)
            {
                expand(n-cap); 
            }
             else if (cap*2 > n)
            {
                expand(); 
            }
        }
    } 
    void IntVector:: assign( unsigned int n, int value )
    {


        if (n > cap)
        {
            if (cap+(n-cap)>cap*2)
            {
                expand(n);
            }
            else if (cap*2 >cap+(n-cap))
            { 
                expand(); 
            }
        }
               sz= n;
    int *ptr = new int[cap];
    for (unsigned int i =0; i < sz; i++)
    {
            ptr[i]=value;
    }
    delete[] data;
    data = new int[cap];
    for (unsigned int j =0; j < sz; j++)
    {
            data[j]=ptr[j];
    }
    delete[] ptr; 
    }
    int &IntVector:: at( unsigned int index )
    {
            
        if (index > sz)
            exit(0); 
        else return *(data + index); 
    }
    int &IntVector:: front( )
    {
        if(sz == 0)
            exit(0);
        return *data;
    }
    int &IntVector:: back( )
    {
                int value; 
        if (sz ==0)
            exit(0); 
        value = sz-1; 
        return *(data+value); 
    }

