#include <iostream> 
#include "instinct.h"
using namespace std;
int instinct_main()
{
        srand(time(NULL)); 
        int i = 0;
        while (i<1) 
        {
            Color color = static_cast<Color>(rand()% 15);
            Circle c = Circle(Point(5,5),rand()%10, color);
            c.set_filled_in(true); 
            win << c;
            win.output_buffer();
        }

    
    
}
