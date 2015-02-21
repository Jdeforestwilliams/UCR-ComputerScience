#include "SortedSet.h"

#include <iostream>
using namespace std;

int main()
{
  
  {
    cout << "\n-----Test IntList copy constructor------------------"
	 << "\n-----Test IntList overloaded =operator--------------";
    cout << "\nlist1 constructor called";
    IntList list1;
    cout << "\npushfront 10";
    list1.push_front( 10 );
    cout << "\npushfront 20";
    list1.push_front( 20 );
    cout << "\npushfront 30";
    list1.push_front( 30 );
    cout << "\nlist1.print: "; 
    list1.print();
    cout << "\nlist2 copy constructor called";
    IntList list2( list1 );
    cout << "\nlist2.print: ";
    list2.print();
    cout << "\nlist3 constructor called";
    IntList list3;
    cout << "\nlist3 = list2";
    list3 = list2;
    cout << "\nlist3.print: ";
    list3.print();
    cout << "\nlist3.push_back(40)";
    list3.push_back( 40 );
    cout << "\nlist3 print: ";
    list3.print();
    cout << "\nlist1 = list2 = list3;";
    list1 = list2 = list3;
    cout << "\nlist1 print: ";
    list1.print();
    cout << "\nlist2 print: ";
    list2.print();    
    cout << "\nlist3 print: ";
    list3.print();
  }
  cout << "\nlist1, list2, list3 destructors finished";
  cout << endl;

 cout << "\n-----Test SortedSet constructors----------------------"
       << "\n-----Test SortedSet =operator-------------------------";
  {
    cout << "\nsset2 constucted";
    SortedSet sset2;
    cout << "\npush_back( 10 )";
    sset2.push_back( 10 );
    cout << "\npush_back( 20 )";
    sset2.push_back( 20 );
    cout << "\npush_back( 30 )";
    sset2.push_back( 30 );
    cout << "\nsset2 print: ";
    sset2.print();

    cout << "\nsset3 constructed";
    SortedSet sset3;
    cout << "\npush_back( 20 )";
    sset3.push_back( 20 );
    cout << "\npush_back( 30 )";
    sset3.push_back( 30 );
    cout << "\npush_back( 40 )";
    sset3.push_back( 40 );
    cout << "\nsset3 print: ";
    sset3.print();
    cout << "\nsset4 copy constructor called (sset3)";
    SortedSet sset4( sset3 );
    cout << "\nsset4 print: ";
    sset4.print();
    cout << "\nsset4 = sset2;";
    sset4 = sset2;
    cout << "\nsset4 print: ";
    sset4.print();
  }
  cout << "\nsset2, sset3, sset4 destructors finished";
  cout << endl;

  {
    cout << "\nlist2 constructed";
    IntList list2;
    list2.push_front( 10 );
    list2.push_front( 20 );
    list2.push_front( 0 );
    list2.push_front( 10 );
    list2.push_front( 30 );
    list2.push_front( 30 );
    list2.push_front( 30 );
    list2.push_front( 0 );
    list2.push_front( 40 );
    list2.push_front( 60 );
    list2.push_front( 50 );
    cout << "\nlist2 print: ";
    list2.print();
    cout << "\nsset5 constructed (list2)"<< endl;
    SortedSet sset5( list2 );
    cout << "\nsset5 print: ";
    sset5.print();
  
    cout << endl;
    cout << "---------Testing | and |= ------------------------------";
    cout << "\nsset6 constructed";
    SortedSet sset6;
    sset6.insert_sorted( 0 );
    sset6.insert_sorted( 10 );
    sset6.insert_sorted( 80 );
    sset6.insert_sorted( 90 );
    sset6.insert_sorted( 100 );
    cout << "\nsset6 print: ";
    sset6.print();
    cout << "\nsset7 constructed";
    SortedSet sset7;
    cout << "\nsset7 = sset6 | sset5;";
    sset7 = sset6 | sset5;
    cout << "\nsset7 print: ";
    sset7.print();
    cout << "\nsset8 constructed";
    SortedSet sset8;
    sset8.insert_sorted( 200 );
    cout << "\nsset8 print: ";
    sset8.print();
    cout << "\nsset8 |= sset7;" ;
    sset8 |= sset7;
    cout << "\nsset8 print: ";
    sset8.print();
  }
  cout << endl;

  cout << "\n----------testing add-------------";
  {
    cout << "\nsset9 constructed";
    SortedSet sset9;
    cout << "\nsset9.add( 50 )";
    sset9.add( 50 );
    cout << "\nsset9 print: ";
    sset9.print();
    cout << "\nsset9.add( 20 )";
    sset9.add( 20 );
    cout << "\nsset9 print: ";
    sset9.print();
    cout << "\nsset9.add( 100 )";
    sset9.add( 100 );
    cout << "\nsset9 print: ";
    sset9.print();
    cout << "\nsset9.add( 30 )";
    sset9.add( 30 );
    cout << "\nsset9.add( 80 )";
    sset9.add( 80 );
    cout << "\nsset9 print: ";
    sset9.print();
    cout << "\nsset9.add( 20 )";
    sset9.add( 20 );
    cout << "\nsset9.add( 30 )";
    sset9.add( 30 );
    cout << "\nsset9.add( 50 )";
    sset9.add( 50 );
    cout << "\nsset9.add( 80 )";
    sset9.add( 80 );
    cout << "\nsset9.add( 100 )";
    sset9.add( 100 );
    cout << "\nsset9 print: ";
    sset9.print();
    cout << endl;

    cout << "\n----------testing in-------------";
    cout << "\nusing sset9";
    cout << "\nsset9 print: ";
    sset9.print();
    cout << "\n20 " << ( sset9.in( 20 ) ? "in" : "not in" );
    cout << "\n30 " << ( sset9.in( 30 ) ? "in" : "not in" );
    cout << "\n50 " << ( sset9.in( 50 ) ? "in" : "not in" );
    cout << "\n80 " << ( sset9.in( 80 ) ? "in" : "not in" );
    cout << "\n100 " << ( sset9.in( 100 ) ? "in" : "not in" );
    cout << "\n0 " << ( sset9.in( 0 ) ? "in" : "not in" );
    cout << "\n25 " << ( sset9.in( 25 ) ? "in" : "not in" );
    cout << "\n40 " << ( sset9.in( 40 ) ? "in" : "not in" );
    cout << "\n90 " << ( sset9.in( 90 ) ? "in" : "not in" );
    cout << "\n200 " << ( sset9.in( 200 ) ? "in" : "not in" );
    cout << endl;

    cout << "\n----------testing & and &= --------";
    cout << "\nsset10 constructed";
    SortedSet sset10;
    sset10.add( 0 );
    sset10.add( 20 );
    sset10.add( 40 );
    sset10.add( 50 );
    sset10.add( 90 );
    sset10.add( 110 );
    cout << "\nsset9 print: ";
    sset9.print();
    cout << "\nsset10 print: ";
    sset10.print();
    cout << "\nsset9 &= sset10";
    sset9 &= sset10;
    cout << "\nsset9 print: ";
    sset9.print();
    sset9.add( 0 );
    sset9.add( 110 );
    cout << "\nsset9 add 0, 110";
    cout << "\nsset9 print: ";
    sset9.print();
    cout << "\nsset10 print: ";
    sset10.print();
    cout << "\nsset11 constructed";
    SortedSet sset11;
    cout << "\nsset11 = sset9 & sset10;";
    sset11 = sset9 & sset10;
    cout << "\nsset11 print: ";
    sset11.print();
  }
  cout << endl;
  cout << endl;
  return 0;
}
