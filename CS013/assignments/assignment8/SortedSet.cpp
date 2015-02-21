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
#include "SortedSet.h"
#include <iostream>
using namespace std; 

SortedSet::SortedSet()
:IntList()
{}
SortedSet::SortedSet( const SortedSet & copy)
:IntList(copy)
{}
SortedSet::SortedSet( const IntList & copy )
:IntList(copy)
{
    select_sort();
    remove_duplicates(); 
}
SortedSet::~SortedSet()
{}
bool SortedSet::in( int data ) const
{
        for (IntNode *current = head; current; current = current -> next)
        {
            if (current->data == data) return true;
        }
        return false; 
}
SortedSet SortedSet::operator|( const SortedSet & rhs ) const
{
    SortedSet temp(*this);
    for (IntNode *curr = rhs.head; curr; curr = curr-> next)
    {
        temp.push_back(curr->data);
    }
    temp.remove_duplicates();
    temp.select_sort(); 
    return temp; 
}
SortedSet SortedSet::operator&( const SortedSet & rhs ) const
{
    SortedSet temp(*this);
    for (IntNode * current = head; current; current = current->next)
    {
        for (IntNode *curr = rhs.head; curr; curr = curr-> next)
        {
            if (current->data == curr -> data)
            temp.push_back(curr->data);
        }    
    }
    temp.select_sort(); 
    return temp; 
}
void SortedSet::add(int data)
{ 
    IntList:: insert_sorted(data);
    remove_duplicates();  
}
void SortedSet::push_front(int data)
{
    for (IntNode *curr = head; curr; curr = curr-> next)
    {
        if (curr->data == data)
        return;
    }  
    add(data);
}
void SortedSet::push_back(int data)
{
    for (IntNode *curr = head; curr; curr = curr-> next)
    {
        if (curr->data == data)
        return;
    }
    add(data);
}
void SortedSet::insert_sorted(int data)
{
    for (IntNode *curr = head; curr; curr = curr-> next)
    {
        if (curr->data == data)
        return;
    }
    add(data);
}
SortedSet SortedSet::operator|=(SortedSet rhs)
{
    for (IntNode *curr = rhs.head; curr; curr = curr-> next)
    {
        push_back(curr->data);
    }
    select_sort(); 
    remove_duplicates();
    return *this;
}
SortedSet SortedSet::operator&=(SortedSet rhs)
{
    SortedSet temp(*this);
    temp.clear();
    for (IntNode * current = head; current; current = current->next)
    {
        for (IntNode *curr = rhs.head; curr; curr = curr-> next)
        {
            if (current->data == curr -> data)
            {
               temp.push_back(curr->data);
            }
        }
    }    
    clear();
    for (IntNode*curr = temp.head; curr; curr = curr->next)
    {
       IntList:: push_front(curr->data);
    }
    select_sort(); 
    return *this;  
}
