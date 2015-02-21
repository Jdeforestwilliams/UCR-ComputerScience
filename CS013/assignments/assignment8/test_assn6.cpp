#include "IntList.h"

#include <iostream>
using namespace std;

int main()
{
  //tests constructor, destructor, push_front, pop_front, print, size
  {
    cout << "\nlist1 constructor called";
    IntList list1;
    cout << "\npushfront 10";
    list1.push_front( 10 );
    cout << "\npushfront 20";
    list1.push_front( 20 );
    cout << "\npushfront 30";
    list1.push_front( 30 );
    cout << "\nlist1: ";
    list1.print();
    cout << "\nSize: " << list1.size();
    cout << "\npop";
    list1.pop_front();
    cout << "\nlist1: ";
    list1.print();
    cout << "\npop";
    list1.pop_front();
    cout << "\nlist1: ";
    list1.print();
    cout << "\npop";
    list1.pop_front();
    cout << "\nlist1: ";
    list1.print();
    cout << "\nSize: " << list1.size();
    cout << endl;
  }
  cout << "list1 destructor called" << endl;

  //tests push_back
  {
    cout << "\nlist2 constructor called";
    IntList list2;
    cout << "\npushback 10";
    list2.push_back( 10 );
    cout << "\npushback 20";
    list2.push_back( 20 );
    cout << "\npushback 30";
    list2.push_back( 30 );
    cout << "\nlist2: ";
    list2.print();
    cout << "\nSize: " << list2.size();
    cout << "\npop";
    list2.pop_front();
    cout << "\nlist2: ";
    list2.print();
    cout << "\npop";
    list2.pop_front();
    cout << "\nlist2: ";
    list2.print();
    cout << "\npop";
    list2.pop_front();
    cout << "\nlist2: ";
    list2.print();
    cout << "\nSize: " << list2.size();
    cout << endl;
  }
  cout << "list2 destructor called" << endl;

  //tests select_sort
  {
    cout << "\nlist5 constructor called";
    IntList list5;
    cout << "\npushfront 10";
    list5.push_front( 10 );
    cout << "\npushfront 20";
    list5.push_front( 20 );
    cout << "\npushfront 30";
    list5.push_front( 30 );
    cout << "\nlist5: ";
    list5.print();
    cout << "\nselect_sort()";
    list5.select_sort();
    cout << "\nlist5: ";
    list5.print();
    cout << "\npop";
    list5.pop_front();
    cout << "\npop";
    list5.pop_front();
    cout << "\npop";
    list5.pop_front();
    cout << "\nlist5: ";
    list5.print();
    cout << "\nselect_sort()";
    list5.select_sort();
    cout << "\nlist5: ";
    list5.print();
    cout << "\npushfront 10";
    list5.push_front( 10 );
    cout << "\nselect_sort()";
    list5.select_sort();
    cout << "\nlist5: ";
    list5.print();
    cout << "\npushfront 20";
    list5.push_front( 20 );
    cout << "\nlist5: ";
    list5.print();
    cout << "\nselect_sort()";
    list5.select_sort();
    cout << "\nlist5: ";
    list5.print();
    cout << endl;
  }
  cout << "list5 destructor called" << endl;

  //tests insert_sorted
  {
    cout << "\nlist6 constructor called";
    IntList list6;
    cout << "\ninsert 20";
    list6.insert_sorted( 20 );
    cout << "\ninsert 10";
    list6.insert_sorted( 10 );
    cout << "\ninsert 30";
    list6.insert_sorted( 30 );
    cout << "\nlist6: ";
    list6.print();
    cout << "\ninsert 50";
    list6.insert_sorted( 50 );
    cout << "\nlist6: ";
    list6.print();
    cout << "\ninsert 40";
    list6.insert_sorted( 40 );
    cout << "\nlist6: ";
    list6.print();
    cout << "\ninsert 11";
    list6.insert_sorted( 11 );
    cout << "\nlist6: ";
    list6.print();
    cout << "\ninsert 10";
    list6.insert_sorted( 10 );
    cout << "\nlist6: ";
    list6.print();
    cout << "\ninsert 11";
    list6.insert_sorted( 11 );
    cout << "\nlist6: ";
    list6.print();
    cout << "\ninsert 9";
    list6.insert_sorted( 9 );
    cout << "\nlist6: ";
    list6.print();
    cout << "\ninsert 50";
    list6.insert_sorted( 50 );
    cout << "\nlist6: ";
    list6.print();
    cout << "\ninsert 51";
    list6.insert_sorted( 51 );
    cout << "\nlist6: ";
    list6.print();
    cout << "\nsize: " << list6.size();
    cout << endl;
  }
  cout << "list6 destructor called" << endl;

  //tests remove_duplicates
  {
    cout << "\nlist8 constructor called";
    IntList list8;
    cout << "\npushfront 10";
    list8.push_front( 10 );
    cout << "\npushfront 20";
    list8.push_front( 20 );
    cout << "\npushfront 10";
    list8.push_front( 10 );
    cout << "\npushfront 30";
    list8.push_front( 30 );
    cout << "\nlist8: ";
    list8.print();
    cout << "\nremove_duplicates()";
    list8.remove_duplicates();
    cout << "\nlist8: ";
    list8.print();
    cout << "\npushfront 10";
    list8.push_front( 10 );
    cout << "\nlist8: ";
    list8.print();
    cout << "\nremove_duplicates()";
    list8.remove_duplicates();
    cout << "\nlist8: ";
    list8.print();
    cout << "\npushfront 20";
    list8.push_front( 20 );
    cout << "\nlist8: ";
    list8.print();
    cout << "\nremove_duplicates()";
    list8.remove_duplicates();
    cout << "\nlist8: ";
    list8.print();
    cout << "\npushfront 20";
    list8.push_front( 20 );
    cout << "\nlist8: ";
    list8.print();
    cout << "\nremove_duplicates()";
    list8.remove_duplicates();
    cout << "\nlist8: ";
    list8.print();
    cout << "\npushfront 20";
    list8.push_front( 20 );
    cout << "\npushfront 20";
    list8.push_front( 20 );
    cout << "\nlist8: ";
    list8.print();
    cout << "\nremove_duplicates()";
    list8.remove_duplicates();
    cout << "\nlist8: ";
    list8.print();
    cout << "\nremove_duplicates()";
    list8.remove_duplicates();
    cout << "\nlist8: ";
    list8.print();
    cout << "\npop";
    list8.pop_front();
    cout << "\npop";
    list8.pop_front();
    cout << "\npush_front(30)";
    list8.push_front(30);
    cout << "\nlist8: ";
    list8.print();
    cout << "\nremove_duplicates()" << flush;
    list8.remove_duplicates();
    cout << "\nlist8: " << flush;
    list8.print();
    cout << "\npush_front(30)";
    list8.push_front(30);
    cout << "\npush_front(30)";
    list8.push_front(30);
    cout << "\nlist8: ";
    list8.print();
    cout << "\nremove_duplicates()" << flush;
    list8.remove_duplicates();
    cout << "\nlist8: " << flush;
    list8.print();
    cout << "\nremove_duplicates()" << flush;
    list8.remove_duplicates();
    cout << "\nlist8: " << flush;
    list8.print();
    cout << "\npop";
    list8.pop_front();
    cout << "\nlist8: ";
    list8.print();
    cout << "\nremove_duplicates()" << flush;
    list8.remove_duplicates();
    cout << "\nlist8: " << flush;
    list8.print();
    cout << endl;
  }
  cout << "list8 destructor called" << endl;

  cout << endl;

  /*
   * Destructor will be tested by looking at code. There is no run-time 
   * test for it. Make sure your destructor actually deletes ALL nodes, not
   * just the head and/or tail.
   */

  return 0;
}
