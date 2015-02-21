#include "IntVector.h" 
#include <iostream>
#include <vector>
using namespace std;
void print( const IntVector & v )
{
  for (unsigned int i = 0; i < v.size(); ++i )
    {
      cout << v.at(i) << " ";
    }
}


int main() 
{
    
    IntVector a(10,20); 
    cout <<"capacity: "<< a.capacity()<< " size: " << a.size() <<endl; 
    print (a); 
    ///////////INSERT FUNCTION/////////
    cout<< endl << "///////////INSERT FUNCTION/////////" << endl; 
    a.insert(5,5); 
    cout <<"capacity: " << a.capacity()<< " size: " << a.size()<< endl;
    print (a); 
    ///////////ERASE FUNCTION/////////
    cout<< endl << "///////////ERASE FUNCTION/////////" << endl;
    IntVector b(5,10); 
    cout <<"capacity: " << b.capacity()<< " size: " << b.size()<< endl;
    b.erase(5);
    cout <<"capacity: " << b.capacity()<< " size: " << b.size()<< endl;
    print(b); 
    ///////////PUSH_BACK FUNCTION/////////
    cout<< endl << "///////////PUSH_BACK FUNCTION/////////" << endl;
    IntVector c(10,30);
    cout <<"capacity: " << c.capacity()<< " size: " << c.size()<< endl;
    c.push_back(5); 
    cout <<"capacity: " << c.capacity()<< " size: " << c.size()<< endl;
    print(c); 
    ///////////POP_BACK FUNCTION/////////
    cout<< endl << "///////////POP_BACK FUNCTION/////////" << endl;
    IntVector d(10,30);
    cout <<"capacity: " << d.capacity()<< " size: " << d.size()<< endl;
    d.pop_back(); 
    cout <<"capacity: " << d.capacity()<< " size: " << d.size()<< endl;
    print(d);
    ///////////CLEAR FUNCTION/////////
    cout<< endl << "///////////CLEAR FUNCTION/////////" << endl;
    IntVector e(10,30);
    cout <<"capacity: " << e.capacity()<< " size: " << e.size()<< endl;
    e.clear(); 
    cout <<"capacity: " << e.capacity()<< " size: " << e.size()<< endl;
    print(e);
    ///////////RESIZE(A) FUNCTION/////////
    cout<< endl << "///////////RESIZE(A) FUNCTION/////////" << endl;
    IntVector f(10,30);
    cout <<"capacity: " << f.capacity()<< " size: " << f.size()<< endl;
    f.resize(5); 
    cout <<"capacity: " << f.capacity()<< " size: " << f.size()<< endl;
    print(f);
    ///////////RESIZE(B) FUNCTION/////////
    cout<< endl << "///////////RESIZE(B) FUNCTION/////////" << endl;
    IntVector g(10,30);
    cout <<"capacity: " << g.capacity()<< " size: " << g.size()<< endl;
    g.resize(20); 
    cout <<"capacity: " << g.capacity()<< " size: " << g.size()<< endl;
    print(g);  
    ///////////RESIZE(A,B) FUNCTION/////////
    cout<< endl << "///////////RESIZE(A,B) FUNCTION/////////" << endl;
    IntVector h(10,30);
    cout <<"capacity: " << h.capacity()<< " size: " << h.size()<< endl;
    h.resize(5,0); 
    cout <<"capacity: " << h.capacity()<< " size: " << h.size()<< endl;
    print(h);
    ///////////RESIZE(C,D) FUNCTION/////////
    cout<< endl << "///////////RESIZE(C,D) FUNCTION/////////" << endl;
    IntVector j(10,30);
    cout <<"capacity: " << j.capacity()<< " size: " << j.size()<< endl;
    j.resize(20,15); 
    cout <<"capacity: " << j.capacity()<< " size: " << j.size()<< endl;
    print(j);  
    ///////////RESERVE FUNCTION/////////
    cout<< endl << "///////////RESERVE FUNCTION/////////" << endl;
    IntVector k(10,30);
    cout <<"capacity: " << k.capacity()<< " size: " << k.size()<< endl;
    k.reserve(20); 
    cout <<"capacity: " << k.capacity()<< " size: " << k.size()<< endl;
    print(k); 
    ///////////ASSIGN FUNCTION/////////
    cout<< endl << "///////////ASSIGN FUNCTION/////////" << endl;
    IntVector l(10,30);
    cout <<"capacity: " << l.capacity()<< " size: " << l.size()<< endl;
    l.assign(20,15); 
    cout <<"capacity: " << l.capacity()<< " size: " << l.size()<< endl;
    print(l); 
    ///////////MUTATOR AT FUNCTION/////////
    cout<< endl << "///////////MUTATOR AT FUNCTION/////////" << endl;
    IntVector m(10,30);
    cout <<"capacity: " << m.capacity()<< " size: " << m.size()<< endl;
    m.at(5)=5; 
    cout <<"capacity: " << m.capacity()<< " size: " << m.size()<< endl;
    print(m); 
    ///////////MUTATOR FRONT FUNCTION/////////
    cout<< endl << "///////////MUTATOR FRONT FUNCTION/////////" << endl;
    IntVector n(10,30);
    cout <<"capacity: " << n.capacity()<< " size: " << n.size()<< endl;
    n.front()=5; 
    cout <<"capacity: " << n.capacity()<< " size: " << n.size()<< endl;
    print(n);
    ///////////MUTATOR BACK FUNCTION/////////
    cout<< endl << "///////////MUTATOR BACK FUNCTION/////////" << endl;
    IntVector q(10,30);
    cout <<"capacity: " << q.capacity()<< " size: " << q.size()<< endl;
    q.back()=5; 
    cout <<"capacity: " << q.capacity()<< " size: " << q.size()<< endl;
    print(q);



    return 0;
}
