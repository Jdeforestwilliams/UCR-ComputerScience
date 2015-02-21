// Course: CS 13 
//
// First Name: Joshua
// Last Name: DeForest-Williams
// ILearn username: jdefo002    
//
// Lecture Section: 001
// Lab Section: 022
// TA: Byung Hyung Kim
//
// Assignment: Assignment 3
//
// I hereby certify that the code in this file
// is ENTIRELY my own original work.
//
// =====================================================
#include <iostream>
using namespace std;
class Rational 
{
    private:
    int num;
    int den;

    public: 
    Rational(int n,int d);
    Rational operator+ (const Rational & j)const ;
    Rational operator- (const Rational & j)const ;
    Rational operator* (const Rational & j)const ;
    Rational operator/ (const Rational & j)const ;
    void display() const ;
    private: 
    int gcd (int n, int d) const; 
    
};
Rational::Rational(int n=0, int d=1)
: num(n), den(d) 
{
    
    int divisor = gcd(num, den); 
    if (d < 0)
    {
        d *= -1; 
        n *= -1; 
    }
    num = n / divisor;
    den = d / divisor; 
}
Rational Rational::operator + (const Rational &j) const
 {
    Rational final(((num*j.den)+(den*j.num)),
        (j.den*den));
    return final;
 } 
Rational Rational:: operator- (const Rational &j) const 
    {
        Rational final(((num*j.den)-(den*j.num)),
            (j.den*den));
        return final;
    }
Rational Rational::  operator* (const Rational &j)const 
    {
        Rational final((num*j.num),(j.den)*den);
        return final;
    }
Rational Rational:: operator/ (const Rational &j)const 
    {
        Rational final((num*j.den),(den*j.num));
        return final;
    }
void Rational:: display() const
{
    if (den == 1)
        cout << num;
    else
        cout << num << "/" << den;
}
int Rational:: gcd(int n, int d) const
{
    while( 1 )
    {
        n = n % d;
		if( n == 0 )
			return d;
		d = d % n;
        
        if( d == 0 )
			return n;
    }
}int main()
{
    int numR1, numR2, numR5;
    int denR1, denR2, denR5;
    int numR3; 
    cout << "Please enter in the numerator for R1: ";
    cin >> numR1; 
    cout << "Please enter in the denominator for R1: ";
    cin >> denR1; 
    cout << "Please enter in the numerator for R2: ";
    cin >> numR2; 
    cout << "Please enter in the denominator for R2: ";
    cin >> denR2; 
    cout << "Please enter in the number for R3: ";
    cin >> numR3; 
    cout << "Please enter in the numerator for R5: ";
    cin >> numR5;
    cout << "Please enter in the denominator for R5: ";
    cin >> denR5; 
    
    
    cout << "\n------- Test Constructors -------";
    
    Rational r1 = Rational(numR1, denR1);
    cout << "\nRational(" << numR1<<","<< denR1<<"): ";
    r1.display();
    Rational r2 = Rational(numR2, denR2);
    cout << "\nRational("<< numR2<<"," << denR2<<"): ";
    r2.display();
    Rational r3 = Rational(numR3);
    cout << "\nRational("<< numR3 << "): ";
    r3.display();
    Rational r4;
    cout << "\nRational(): ";
    r4.display();
    cout << endl;
    
    //A few extra test values for later tests.
    Rational r5(numR5,denR5);
    Rational result;
    
    cout << "\n------- Test + -------\n";
    
    //Result should be 13/6
    result = r1 + r2;
    r1.display();
    cout << " + ";
    r2.display(); 
    cout << " = ";
    result.display();
    cout << endl;
    
    //Result should be 11/2
    result = r1 + r3;
    r1.display();
    cout << " + ";
    r3.display(); 
    cout << " = ";
    result.display();
    cout << endl;
    
    //Result should be 4
    result = r1 + r5;
    r1.display();
    cout << " + ";
    r5.display(); 
    cout << " = ";
    result.display();
    cout << endl;
    
    cout << "\n------- Test - -------\n";
    
    //Result should be 5/6
    result = r1 - r2;
    r1.display();
    cout << " - ";
    r2.display(); 
    cout << " = ";
    result.display();
    cout << endl;
    
    //Result should be 5/2
    result = r3 - r1;
    r3.display();
    cout << " - ";
    r1.display(); 
    cout << " = ";
    result.display();
    cout << endl;
    
    //Result should be 1
    result = r5 - r1;
    r5.display();
    cout << " - ";
    r1.display(); 
    cout << " = ";
    result.display();
    cout << endl;
    
    cout << "\n------- Test * -------\n";
    
    //Result should be 1
    result = r1 * r2;
    r1.display();
    cout << " * ";
    r2.display(); 
    cout << " = ";
    result.display();
    cout << endl;
    
    //Result should be 6
    result = r1 * r3;
    r1.display();
    cout << " * ";
    r3.display(); 
    cout << " = ";
    result.display();
    cout << endl;
    
    //Result should be 15/4
    result = r1 * r5;
    r1.display();
    cout << " * ";
    r5.display(); 
    cout << " = ";
    result.display();
    cout << endl;
    
    cout << "\n------- Test / -------\n";
    
    //Result should be 9/4
    result = r1 / r2;
    r1.display();
    cout << " / ";
    r2.display(); 
    cout << " = ";
    result.display();
    cout << endl;
    
    //Result should be 3/8
    result = r1 / r3;
    r1.display();
    cout << " / ";
    r3.display(); 
    cout << " = ";
    result.display();
    cout << endl;
    
    //Result should be 3/5
    result = r1 / r5;
    r1.display();
    cout << " / ";
    r5.display(); 
    cout << " = ";
    result.display();
    cout << endl;
    
    cout << endl;
    
    cout << "\n------- A few advanced tests -------";
    
    //Should display -1/2
    Rational r6 = Rational(-1, 2);
    cout << "\nRational(-1, 2): ";
    r6.display();
    
    //Should display -1/2
    Rational r7 = Rational(1, -2);
    cout << "\nRational(1, -2): ";
    r7.display();
    cout << endl;
    
    //Result should be -5/2
    result = r1 - r3;
    r1.display();
    cout << " - ";
    r3.display(); 
    cout << " = ";
    result.display();
    cout << endl;
    
    //Result should be -5/2
    result = r6 / r1;
    r6.display();
    cout << " / ";
    r1.display(); 
    cout << " = ";
    result.display();
    cout << endl;
    
    return 0; 
}
