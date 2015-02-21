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
#include <iostream>
#include "IntList.h"
using namespace std;

IntList:: IntList()
    :head(NULL), tail(NULL), sz(0)
    {}
IntList:: ~IntList()
{
    delete head;
    delete tail; 
}
unsigned int IntList::  size() const
    {
        return sz; 
    }
void IntList:: print() const
    {
        for (IntNode *current = head; current!= NULL; current = current -> next)
        {
            cout << current->data << " " ;
        }
        if(!head)
        {
            for (IntNode *current = tail; current!= NULL; current = current -> next)
            {
                cout << current->data << " " ;
            }            
        } 
    }
void IntList:: push_front(int value)
{
       IntNode *new_node = new IntNode(value); 
       new_node-> next = head;
       head = new_node; 
       sz++;
       if (!tail)
            tail = head;
}
void IntList:: push_back(int value)
{
    IntNode *new_node = new IntNode(value);
     if (sz ==0)
    {
        head = new_node;
        tail = new_node;
        sz++; 
        return; 
    } 
    tail-> next = new_node; 
    tail = new_node; 
    sz++;
}
void IntList:: pop_front()
{
    if (sz == 0)
        return;
    IntNode *temp = head;
    head = head-> next;
    delete temp;
    sz--;
    if(!head) 
        tail = NULL;
}
void IntList:: select_sort()
{
    if (sz == 0|| sz == 1)
    {
        return;
    }
    else if(sz == 2)
    {
        IntNode *i = head;
        IntNode* j = i->next;
        if(i-> data > j-> data)
        {
            swap(i-> data, j-> data); 
        }
        return; 
    }
    else 
    {
        for (IntNode *i = head; (i-> next) != tail;i= i-> next)
        {   
            IntNode *smallest = i;
            for (IntNode* j = i->next; j != NULL;j= j-> next)
            { 
                if (smallest->data > j->data)
                    {
                        smallest = j;
                    }
            }
            swap(i-> data, smallest-> data);
        }
    }
}
void IntList:: insert_sorted(int value)
{
   check_sorted(); 
    
    if (sz == 0)
    {
        push_front(value);
        return; 
    }
    else if (sz == 1)
    {
        if (value >= head->data)
            push_back(value);
        else if (value < head->data)
            push_front(value);
    }
    else if (value <= head->data)
        push_front(value);
    else
    { 
        IntNode *new_node = new IntNode(value); 
        IntNode *current = head;
        IntNode *previous;
        while (current && current->data <= new_node->data)
        {
            previous = current;
            current = current -> next;
        }
        previous -> next = new_node;
        new_node -> next = current;
        sz++;
    } 
}
void IntList:: remove_duplicates()
{
    IntNode * h = head;
    IntNode * p;
    IntNode * previous;
    while (h != NULL) 
    {
        previous = h;
        p = h -> next;
        for (; p != NULL;  p = p-> next) 
        {
            if ( p-> data == h-> data ) 
            {
                previous -> next = p->next;
                p->next = NULL;
                delete p-> next; 
                p = previous;
            }
            previous = p;
        }
        h = h -> next; 
    }
}    
void IntList:: check_sorted()
{ 
    if (sz == 0 || sz == 1) return;
    bool sorted = true; 
    for (IntNode *i = head; (i-> next) != tail;i= i-> next)
    {   
        for (IntNode* j = i->next; j != NULL;j= j-> next)
        {
                if (i-> data > j->data)
                {
                    sorted = false; 
                }
        }
    }
    if (sorted == false)
       {
        select_sort(); 
        }
}
IntList::IntList( const IntList & copy)
: head(NULL), tail(NULL), sz(0)
{
    IntNode * curr = copy.head;
    for (; curr; curr = curr-> next)
    {
        push_back(curr->data);
    }
    }
const IntList &IntList::  operator=( const IntList & rhs)
{
    if (this == & rhs)
    return *this;
    clear(); 
    IntNode * curr = rhs.head;
    for (; curr; curr = curr-> next)
    {
        push_back(curr->data);
    }
    return *this; 
    }
void IntList:: clear()
{
    IntNode * curr = head;
    for (; curr; curr = curr-> next )
    {
        pop_front();
    }
  
}
