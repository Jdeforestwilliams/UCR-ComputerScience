// Course: CS 13 <Spring 2012>
//
// First Name: Jdefo002
// Last Name: Deforest-Williams
// Course username: <jdefo002>
// email address: <jdefo002@ucr.edu>
//
// Lecture Section: <001>
// Lab Section: <022>
// TA: Byung
//
// Assignment: <assn7>
//
// I hereby certify that the code in this file
// is ENTIRELY my own original work.
//
// =================================================================
#include <iostream> 
#include <fstream>
using namespace std;
int gcd(int a,int b)
{   
    if (b == 0)
       return a;
    else
       return gcd(b, a % b);
}
void substitutionMethod(int a, int b, int c, int &x, int &y)
{
    if (c % gcd(a,b)  != 0)
    {
        return;
    }
    else if (a % b == 0)
    {
        x = 0;
        y = c/b;
    }
    else
    { 
        int q = (a/b);
        int r = (a%b); 
        int u = 0;
        int v = 0; 
        substitutionMethod(b,r,c,u,v);       
        x = v; 
        y = u - q*x;

    }
}
int main()
{
    int x = 0;
    int y = 0; 
    string in_file;
    string out_file;  
    cout << "Please enter the name of the .txt file you want to input: "; 
    cin >> in_file;
    cout << "Please enter the name of the .txt file you want to output: "; 
    cin >> out_file;
 
    ifstream fin( in_file.c_str()); 
    if(fin.fail())
    {

        cout << "Error";
        exit(0); 
    } 
    ofstream fout(out_file.c_str());
    if(fout.fail())
    {

        cout << "Error";
        exit(0); 
    }
    int a;
    int b;
    int c;
    
    do
    {
        fin >> a >> b >> c;
        substitutionMethod(a,b,c, x,y); 
        if (c % gcd(a,b)  != 0)
        {
            fout << "Not Solution! " << endl;
        }
        else
            {
            fout << x << " " << y<< endl; 
        }
    }while (!fin.eof());
}
