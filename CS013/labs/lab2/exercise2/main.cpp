#include <iostream>
#include <time.h> 
#include <math.h> 
using namespace std;

const double rand_max = 10; 

/*This function generates a random double value between a and b*/
double rand_float(double a, double b)
{
return ((double)rand()/RAND_MAX)*(b-a) + a;
}

int rand_integer(int a, int b) 
{
    int random_number = a + (rand()%(b-a));
    return random_number; 
    }
 void remove_number(double arr1[], int index, int &size)
 {
    for (int r =index ; r < size-1; r++)
    {
            arr1[r] = arr1[r+1];
    }
    size--;
}
int main()
{
    srand(time(0)); 
    const double a1 = 4 + (sqrt(6)/2);
    const double b1 = 4 - (sqrt(6)/2); 
    const double theo_mean1 = (a1+b1)/2;
    const double theo_var1 = ((b1-a1)*(b1-a1))/12;
    
    const double a2 = 4 + sqrt(6);
    const double b2 = 4 - sqrt(6);
    const double theo_mean2 = (a2+b2)/2;
    const double theo_var2 = ((b2-a2)*(b2-a2))/12;
    
    
    int size = 500; 
    double arr1[size]; 
    double arr2[size]; 
    for (int i = 0; i < size; i++)
    { 
        arr1[i] = rand_float(a1,b1); 
        arr2[i] = rand_float(a2,b2); 
    }
    double a = 0; 
    double b = 0; 
    int c = 0;
    int d = 0; 
    double compute_mean = 0; 
    double compute_var= 0;
    for (int j = 0; j < size; j++)
    {
        c = rand_integer(0, size-1);
        a= arr1[c]; 
        remove_number(arr1,c, size);
        d = rand_integer(0, size-1);  
        b= arr1[d];
        remove_number(arr1,d,size);
        compute_mean = (a+b)/2;
        compute_var = ((b-a)*(b-a))/12;
        cout <<"Computed Mean For Sequnce 1: " <<  compute_mean << endl << 
        "Computed Var. For Sequnce 1: " << compute_var << endl; 
    }
     a = 0; 
    b = 0; 
    c = 0;
    d = 0; 
    compute_mean = 0; 
    compute_var= 0;
    for (int j = 0; j < size; j++)
    {
        c = rand_integer(0, size-1);
        a= arr1[c]; 
        remove_number(arr1,c, size);
        d = rand_integer(0, size-1);  
        b= arr1[d];
        remove_number(arr1,d,size);
        compute_mean = (a+b)/2;
        compute_var = ((b-a)*(b-a))/12;
        cout <<"Computed Mean For Sequnce 2: " <<  compute_mean << endl << 
        "Computed Var. For Sequnce 2: " << compute_var << endl; 
    }
    cout << "Theoretical Mean For Sequence 1:  " << theo_mean1 << endl;
    cout << "Theoretical Variance For Sequence 1: " << theo_var1 << endl; 
    
    cout << "Theoretical Mean For Sequence 2: " << theo_mean2 << endl;
    cout << "Theoretical Variance For Sequence 2: " << theo_var2 << endl; 
}
