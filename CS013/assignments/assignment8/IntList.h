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

#ifndef NULL
#define NULL 0
#endif

class IntNode
{
  public:
    int data;
    IntNode *next;
    IntNode( int data ) : data(data), next(NULL) {}
};

class IntList
{
    protected:
    IntNode* head;
    IntNode* tail; 
    unsigned int sz;
    public: 
    IntList();
    IntList( const IntList & );
    ~IntList();
    unsigned int size() const;
    void print() const;
    void push_front(int value);
    void push_back(int value);
    void pop_front();
    void select_sort();
    void insert_sorted(int value);
    void remove_duplicates();
    const IntList & operator=( const IntList & );
    void clear();

    private: 
    void check_sorted(); 
};
