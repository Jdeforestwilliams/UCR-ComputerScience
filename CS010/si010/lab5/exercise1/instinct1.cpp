#include "instinct.h"
#include <string>
int instinct_main()
{
    double scale = win.get_double ("Please enter in a scale: ");
    double r_width = 2.0 * scale;
    double r_length = 2.0 * scale
    Rect r = Rect(Point(1.0,1.0), r_width, r_length, RED, true);

    win << r;
    win.output_buffer();
    return 0;
}
