#include <iostream>
#include "IntList.h"
using namespace std;
int main()
{
    IntList a;
    
    int push_front1,push_front2,push_front3,push_front4,push_back1,push_back2,
            push_back3,push_back4,push_back5, push_front5,push_front6,
            push_front7,push_front8,push_front9,push_back6,push_back7,
            push_back8,push_back9,push_back10;
    cout << "Enter value for push_front: " << endl; 
    cin >> push_front1; 
    a.push_front(push_front1);
    cout << "Enter value for push_front: " << endl; 
    cin >> push_front2;
    a.push_front(push_front2);
    cout << "Enter value for push_front: " << endl; 
    cin >> push_front3;
    a.push_front(push_front3);
    cout << "Enter value for push_front: " << endl; 
    cin >> push_front4;
    a.push_front(push_front4);
    cout << "Enter value for push_back: " << endl; 
    cin >> push_back1;
    a.push_back(push_back1);
        cout << "Enter value for push_back: " << endl; 
    cin >> push_back2;
    a.push_back(push_back2);
    cout << "Enter value for push_back: " << endl; 
    cin >> push_back3;
    a.push_back(push_back3); 
    cout << "Enter value for push_back: " << endl; 
    cin >> push_back4;
    a.push_back(push_back4); 
    cout << "Enter value for push_back: " << endl; 
    cin >> push_back5;
    a.push_back(push_back5);
    cout << "Enter value for push_front: " << endl; 
    cin >> push_front5; 
    a.push_front(push_front5);
    cout << "Enter value for push_front: " << endl; 
    cin >> push_front6;    
    a.push_front(push_front6);
    cout << "Enter value for push_front: " << endl; 
    cin >> push_front7; 
    a.push_front(push_front7);
    cout << "Enter value for push_front: " << endl; 
    cin >> push_front8; 
    a.push_front(push_front8);
    cout << "Enter value for push_front: " << endl; 
    cin >> push_front9; 
    a.push_front(push_front9);
    cout << "Enter value for push_back: " << endl; 
    cin >> push_back6;     
    a.push_back(push_back6);
    cout << "Enter value for push_back: " << endl; 
    cin >> push_back7; 
    a.push_back(push_back7);
    cout << "Enter value for push_back: " << endl; 
    cin >> push_back8; 
    a.push_back(push_back8); 
    cout << "Enter value for push_back: " << endl; 
    cin >> push_back9; 
    a.push_back(push_back9); 
    cout << "Enter value for push_back: " << endl; 
    cin >> push_back10; 
    a.push_back(push_back10);
    a.print();
    cout << endl; 
    //~ a.pop_front();
    //~ a.pop_front();
    //~ a.pop_front();
    //~ a.pop_front();
    //~ a.pop_front();
    a.print(); 
    cout << endl; 
    a.select_sort();
    a.print(); 
    cout << endl; 
    a.insert_sorted(100);
    a.print();
    cout << endl; 
    a.pop_front();
    a.pop_front();
    a.insert_sorted(0);
    a.print(); 
    //~ IntList b; 
    //~ b.insert_sorted(55); 
    //~ b.print();
    //~ cout << endl;
    //~ b.push_back(10);
    //~ b.print();
    //~ cout << endl;
    //~ b.push_back(6);
    //~ b.print();
    //~ cout << endl;
    //~ b.insert_sorted(8);
    //~ b.print();
    //~ cout << endl;
    //~ b.insert_sorted(12);
    //~ b.print();
    //~ cout << endl;
}
