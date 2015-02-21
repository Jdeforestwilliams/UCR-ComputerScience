#include <iostream> 

using namespace std;

int main ()
{
    double dollar ;
    double euros = .74 ;
    double yen = 99.6 ;
    double rand = 9.07 ;
    double rupees = 49.90 ;
    double pesos = 13.83 ;
    cout << "Please enter US Dollars $" ;
    cin >> dollar ;
    double totaleuro = dollar * euros ;
    double totalyen = dollar * yen;
    double totalrand = dollar * rand;
    double totalrupees = dollar * rupees;
    double totalpesos = dollar * pesos;
    //conversion forumla
    cout << " " << endl;
    cout << "Euros: " << totaleuro << endl;
    cout << "Yen: " << totalyen << endl;
    cout << "Rand: "<< totalrand << endl;
    cout << "Rupees: " << totalrupees << endl;
    cout << "Pesos: " <<totalpesos << endl;
    return 0;
}
