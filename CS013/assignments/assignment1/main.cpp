// Course: CS 13 <Spring 2012>
//
// First Name: Joshua 
// Last Name: DeForest-Williams
// Course username: <jdefo002>
// email address: <jdefo002@ucr.edu>
//
// Lecture Section: <001>
// Lab Section: <022>
// TA: Byung Hyung Kim
//
// Assignment: <Assginment 1>
//
// I hereby certify that the code in this file
// is ENTIRELY my own original work.
//
// =================================================================
#include <iostream>
#include <fstream>
#include <string> 
using namespace std; 
const int FLIGHT_PATH_SIZE = 40; 

void display(double arr[],double arr2[], int size)
{
    for (int i = 0; i < size; i++)
    {
            cout << arr[i] << " " << arr2[i] << endl;
    }
}

double interpolation(double arr[],double arr1[], int input, int size)
{
    double fb; 
    for (int i = 0; i < size; i++)
    {
            if (arr[i] == input)
            {
                    fb = arr1[i]; 
                    return fb; 
            }
    }
    int i = size; 
    double a;
    double c;
    double fa; 
    double fc; 
    while (i >0)
    {
            if (input > arr[i-1] && input < arr[i])
            {
                cout << i; 
                a = arr[i-1];
                c = arr[i];
                fa = arr1[i-1]; 
                fc = arr1[i];
            }
           i--; 
    }
    cout << a << " " << c << " " << fa << " " << fc << " " << input ; 
    double b = (double)input;
     
    fb = fa + (b - a)/(c - a)*(fc - fa);
     
    return fb;  
}
bool ordered( double arr1[], int size)
{
   

 
    for (int i = 0; i < (size - 1); i++)
    {
        if (arr1[i] > arr1[i+1])
        {
       
        return false; 
        }
    }

 
  return true; 
}
void reorder (double  arr[], double arr1[], int size)
{
    for (int i=0; i < size-1; i++)
    {

            int pos_small = i; 
            for (int j = i+1; j < size; j++)
            {
                if (arr[j] < arr[pos_small])
                {
                    pos_small = j; 
                }
            }
        swap(arr[pos_small], arr[i]);
        swap(arr1[pos_small], arr1[i]); 
    }
}


int main()
{
    string data_name; 
    cout << "Please enter a the name of the .dat file: "; 
    cin >> data_name;
    
    ifstream fin( data_name.c_str()); 
    if(fin.fail())
    {
        cout << "Error";
        exit(0); 
    } 
    
   
    int size = 0; 
    int i = 0;
    double arr1[FLIGHT_PATH_SIZE];
    double arr2[FLIGHT_PATH_SIZE];
    while (!fin.eof())
    {
        fin >> arr1[i] >> arr2[i];
        size++;
        i++;
    }
  
     
    if(ordered(arr1, size) == false)
    {
        reorder(arr1, arr2, size);
    }
    //display(arr1,arr2,size);
    int input; 
    do
    {
    cout << "Please Enter in a flight path angle (-100 to quit): ";
    
    cin >> input; 
    cout << "Your Flight Path Coefficient is: " << 
    interpolation(arr1,arr2,input,size) << endl; 
    }while(input != -100); 
    return 0; 
        
}
