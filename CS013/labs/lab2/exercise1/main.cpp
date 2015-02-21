#include <iostream>
#include <time.h> 
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
    double a = 4;
    double b = 10;

    double theo_mean = (a+b)/2;
    double theo_var = ((b-a)*(b-a))/12;
    int size = 1000; 
    double arr1[size]; 
    for (int i = 0; i < size; i++)
    { 
        arr1[i] = rand_float(a,b); 
    }
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
        cout <<"Computed Mean " <<  compute_mean << 
        " Computed Variance " << compute_var << endl; 
    }
    cout << "Theoretical Mean  " << theo_mean << endl;
    cout << "Theoretical Variance " << theo_var << endl; 
    

}
