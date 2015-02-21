#include <vector>
#include <iostream>

using namespace std;

// TODO: Write function is_magic
// Takes in a magic square and an integer
// Returns true if the sums for the rows, columns and diagonals
//    of the square are the same as the provided integer. 
//    Otherwise returns false.

bool is_magic(vector<vector<int> > v, int n)
{
   
   // tests columns
    int sum = 0;
    int sum1 = 0; 
    
    for (int j = 0; j < n-1; j++)
    {
       for (int i = 0; i < n; i++)
       {
           sum += v.at(i).at(j);
          
           sum1 += v.at(i).at(j+1);
        
        }
        if (sum != sum1)
        return false;
    }
    
    // test rows
    int sum2 = 0;
    int sum3 = 0; 
    for (int i = 0; i < n-1; i++)
    {
        for (int j =0; j < n; j++)
        {
            sum2 += v.at(i).at(j);
            sum3 += v.at(i+1).at(j);
        }
        if (sum2 != sum3)
            return false; 
    }
    if (sum1 != sum2)
    {
        
        return false;
    } 
    // test diagonal 1
    int sum4 =0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(i == j)
            sum4 += v.at(i).at(j);
        }
    }
    //test diagonal 2
    int sum5 = 0;
    for (int i =n; i>= 0; i--)
    {
        for(int j= 0; j<n; j++)
        {
            if((i+j) == (n-1))
            sum5+=v.at(i).at(j); 
        }
    }

    if (sum5 != sum4) 
    {
        
        return false; 
    }
   return true;  
}
void get_values( vector<vector<int> > &magic_square, int &n)
{
   vector<int> inputs;
   int entry;
   
   while (cin >> entry)
      inputs.push_back(entry);
   
   for (n = 1; n * n < inputs.size(); ++n)
      ;
   
   if (n * n != inputs.size())
   {
      cout << "Input error: " << inputs.size() 
           << " not a valid number of inp uts." << endl;
      n = 0;
      return;
   }
   
   int i = 0;
   for (int r = 0; r < n; ++r)
   {
      vector<int> row(n);
      for (int c = 0; c < n; ++c)
      {
         row.at(c) = inputs.at(i);
         ++i;
      }
      magic_square.push_back(row);
   }
}

void display_square(const vector<vector<int> > &v, string delim)
{
   for (int r = 0; r < v.size(); ++r)
   {
      for (int c = 0; c < v.at(r).size(); ++c)
      {
         cout << v.at(r).at(c) << delim;
      }
      cout << endl;
   }
}

int main()
{
   vector<vector<int> > magic_square;
   int n;
   get_values(magic_square, n);
   if (n == 0)
      return 0;
   display_square(magic_square, " ");
   if (is_magic(magic_square, n))
      cout << "It is a magic square." << endl;
   else
      cout << "Not a magic square." << endl;
   
   return 0;
}
