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
// Assignment: <assn6>
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
        for (IntNode *curr = head; curr!= NULL; curr = curr -> next)
        {
            cout << curr->data << " " ;
        }
        if(!head)
        {
            for (IntNode *curr = tail; curr!= NULL; curr = curr -> next)
            {
                cout << curr->data << " " ;
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
void IntList:: insert_sorted(int value)
{
   check_sorted(); 

        

        IntNode *new_node = new IntNode(value); 
        for (IntNode *i = head; (i-> next) != tail;i= i-> next)
        {   
            if (sz == 0)
            {
                push_front(value);
                return; 
            }
            else if (sz == 1)
            {
               if ( new_node-> data < i-> data)
               {
                    push_front(value); 
                } 
                else if (new_node->data >= i->data)
                {
                    push_back(value); 
                }
            }
            if (i -> next != NULL)
           { 
                if (i->data <= new_node->data
                        &&  i->next->data >= new_node-> data)
                {
                    new_node-> next = i->next;
                    i->next = new_node; 
                    sz++;
                    return; 
                }
            }
           else if(i -> next == NULL)
           {
               if (i->data < new_node-> data)
               {
                    i->next = new_node; 
                    tail = new_node;
                    sz++;
                    return; 
                }
            }
        }
    }

void IntList:: removed_duplicates()
{
    
}    

void IntList:: check_sorted()
{ 
    if (sz == 0) return;
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
