#include "instinct.h"
#include <string>
int instinct_main()
{
    double scale = win.get_double ("Please enter in a scale: ");

    Rect r = Rect(Point(1.0,1.0), 2.0 * scale, 2.0 * scale, RED, true);
    Rect s = Rect(Point(1.0,3.0), 2.0 * scale, 2.0 * scale, GREEN, true);
    Rect t = Rect(Point(3.0,3.0), 2.0 * scale, 2.0 * scale, BLACK, true);
    Rect u = Rect(Point(3.0,1.0), 2.0 * scale, 2.0 * scale, PURPLE, true);
    win << r << s << t << u;
    win.output_buffer();
    return 0;
}
