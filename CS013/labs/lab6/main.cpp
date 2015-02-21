#include "Date.h"
#include <iostream>
#include <string>

using namespace std;

int main(){

   Date xmas(12,25,2010);
   Date mothers("May", 9, 2010);
   Date nothing;
   
   cout<<"Christmas \n\t";
   xmas.print_alpha();
   cout<<"\n\t";
   xmas.print_numeric();
   cout<<endl<<endl;
   
   cout<<"Mother's Day \n\t";
   mothers.print_alpha();
   cout<<"\n\t";
   mothers.print_numeric();
   cout<<endl<<endl;
   
   cout<<"Default \n\t";
   nothing.print_alpha();
   cout<<"\n\t";
   nothing.print_numeric();
   cout<<endl<<endl;
   
   return 0;
}
