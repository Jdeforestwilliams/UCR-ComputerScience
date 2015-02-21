#include <iostream>
#include <time.h>
using namespace std;

int random_person_index(int array_size)
//returns an integer between 0 and (array_size - 1)
{
    int random_person = (rand()% array_size);
    return random_person; 
    
    }
    void remove_person(string roster[], int index, int size)
 //"removes" name at index from roster[]
 {
     string temp = roster[size-1]; 
     roster[size-1] = roster[index];
     roster[index] = temp; 
     }
void make_teams(string roster[], string a[], string b[], int &roster_size) 
//assigns names to a[] and b[] given roster[]
{
    int index;
        for (int i = 0; i < 5; i++)
        {
           
            
                index = random_person_index(roster_size);
                a[i] = roster[index];
                remove_person(roster,index, roster_size);
                roster_size--; 
                index = random_person_index(roster_size); 
                
                b[i] = roster[index];
               remove_person(roster,index, roster_size);
                roster_size--; 
               
        }
    }

void display(const string arr[], int arr_size)
//displays a team's members
{
    for (int i = 0; i < arr_size; i++)
    {
        cout << arr[i]<< ' ';
    }
}
int main()
{
    srand(time(0));
    string roster[10]; 
    string ateam[5];
    string bteam[5];
    string name;
    int r = 0;
    while (cin >> name && r < 10)
    {
        roster[r] = name;
        r++; 
    }
    make_teams(roster, ateam, bteam, r);
    cout << "Team A: " << endl;
    cout << "   ";
    display(ateam, 5);
    cout << endl; 
    cout << "Team B: " << endl;
    cout << "   ";
    display(bteam, 5);
    cout << endl; 
  }
