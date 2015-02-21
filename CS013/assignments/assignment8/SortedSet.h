// Course: CS 13 <Spring 2012>
//
// First Name:Joshua
// Last Name:DeForest-Williams
// Login id: <jdefo002>
// email address: <jdefo002@ucr.edu>
//
// Lecture Section: <001>
// Lab Section: <022>
// TA:Byung Hyung Kim 
//
// Assignment: <assn8>
//
// I hereby certify that the code in this file
// is ENTIRELY my own original work.
//
// ================================================================
#ifndef __SORTEDSET_H__
#define __SORTEDSET_H__
#include "IntList.h"
class SortedSet : public IntList
{
    public:
    SortedSet();
    SortedSet( const SortedSet & );
    SortedSet( const IntList & );
    ~SortedSet();
    bool in( int data ) const;
    SortedSet operator|( const SortedSet & ) const; 
    SortedSet operator&( const SortedSet & ) const;
    void add(int data);
    void push_front(int data);
    void push_back(int data); 
    void insert_sorted(int data); 
    SortedSet operator|=(SortedSet);
    SortedSet operator&=(SortedSet); 
};
#endif
