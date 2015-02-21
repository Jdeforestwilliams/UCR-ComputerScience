#include <iostream>
using namespace std;
class Rational 
{
    private:
    int num;
    int den;

    public: 
    Rational()
    {
        num=1;
        den=1;   
    }
    
    void Initialize(int x, int y)
    {
        num = x;
        den = y; 
    }
    int Numerator(Rational j)
    {
        return num;
    }
    int Denominator(Rational j)
    {
        return den; 
    }
    
    Rational Addition(Rational j)
    {
        Rational final;
        final.Initialize(((num*j.Denominator(j))+(den*j.Numerator(j))),
            (j.Denominator(j)*den));
        return final;
    }
    Rational Subtraction(Rational j)
    {
        Rational final;
        final.Initialize(((num*j.Denominator(j))-(den*j.Numerator(j))),
            (j.Denominator(j)*den));
        return final;
    }
    Rational Multiplication(Rational j)
    {
        Rational final;
        final.Initialize(((num*j.Numerator(j))),(j.Denominator(j)*den));
        return final;
    }
    Rational Division(Rational j)
    {
        Rational final;
        final.Initialize((num*j.Denominator(j)),(den*j.Numerator(j)));
        return final;
    }
    void Output()
    {
            cout << num << "/" << den << endl;
    }
};
int main()
{
    Rational Fraction1;
    Rational Fraction2; 
    Rational final; 
    int num1;
    int num2;
    int den1;
    int den2;
    int choice; 
    cout << "Please enter in the value of your first numerator: " ;
    cin >> num1; 
    cout << "Please enter in the value of your first denominator: ";
    cin >> den1;
    cout <<"Please enter in the value of your second numerator: " ;
    cin >> num2;
    cout <<"Please enter in the value of your second denominator : ";
    cin >> den2;
    Fraction1.Initialize(num1,den1);
    Fraction2.Initialize(num2,den2);  
    cout <<"A: "<< num1 << "/"<<den1 << endl <<
    "B: "<< num2<< "/"<< den2<< endl <<
    "1. Addition (A + B)"<< endl <<
    "2. Subtraction (A - B)"<< endl <<
    "3. Multiplication (A * B)"<< endl <<
    "4. Division (A / B)" << endl <<
    "Please select (1-4) from the menu:" << endl;
    cin >> choice;
    switch(choice)
    {
        case 1: final = Fraction1.Addition(Fraction2); final.Output();
            break;
        case 2: final = Fraction1.Subtraction(Fraction2);final.Output();
            break;
        case 3: final = Fraction1.Multiplication(Fraction2); final.Output();
            break;
        case 4: final = Fraction1.Division(Fraction2); final.Output();
            break;
    
  }
    return 0; 
}
