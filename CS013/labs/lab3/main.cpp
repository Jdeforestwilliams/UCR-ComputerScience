#include <iostream> 
#include <iomanip> 
using namespace std;
void table_set(int a[][13])
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            a[i][j] = (i*j);
        }
    }
}
int main()
{
    int table[13][13];
    table_set(table);
    for (int i = 0; i <= 12; i++)
    {
            for (int j = 0; j <= 12; j++)
            {
                    if (i !=0 && j !=0)
                    {
                            cout << fixed << setprecision(2) << 
                            setw(3) << table[i][j] << " " ;
                    }
            }
        cout << endl; 
    }
    return 0; 
}
