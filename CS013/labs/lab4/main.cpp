#include <iostream> 
#include <cstring>
using namespace std;
char * cstrcpy ( char * destination, const char * source )
{
    int x = strlen(source); 
 

    for (int i = 0; i < (x+1); i++)
    {
            destination[i]=source[i]; 
    }
    
    return destination; 
}
int strcmp ( const char * str1, const char * str2 )
{
    int x = strlen(str1); 
    int y = strlen(str2); 
    int z = 0; 
    for (int i = 0; i < x && i < y; i++,str1++,str2++)
    {
            if(*str1 == *str2)
            z =0;
            else if (*str1 > *str2)
            {
                z = 1;
                break;
            }
            else if (*str1 < *str2)
            {
                    z = -1; 
                    break; 
            }
        
    }
    return z; 
}
const int MAX = 80;
int main()
{
    char arr1[MAX];
    char arr2[MAX] = {'a','b','c','d','e'} ; 
    cout << cstrcpy(arr1,arr2)<< " "; 
    
    //char arr3[MAX] = {'a','b','c','d','e'};
    char arr3[MAX] = {'e','a','b','c','d'};
    char arr4[MAX] = {'a','b','c','d','e'};
    //char arr4[MAX] = {'e','a','b','c','d'};
    cout << strcmp(arr3,arr4) << " "; 
    return 0; 
}
