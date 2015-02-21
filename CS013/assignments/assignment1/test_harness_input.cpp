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
int main()
{
    string data_name; 
    cout << "Please enter a the name of the .dat file: "; 
    cin >> data_name;
    
    ifstream fin( data_name.c_str()); 
    if(fin.fail())
    {
        cout << "Error";
        exit(1); 
    } 
    fin.open("data_name");
    double number; 
    int size = 0; 
    double arr1[FLIGHT_PATH_SIZE];
    double arr2[FLIGHT_PATH_SIZE];
    while (fin >> number)
    {
        arr1[size] = number;
        arr2[size] = number;
        size++;
    }
    display(arr1, arr2, size);
    cout << "1"; 
}
