#include "instinct.h"
int instinct_main()
{
    Rect r = Rect(Point(1.0,1.0), 2.0, 2.0, RED, true);
    Rect s = Rect(Point(1.0,3.0), 2.0, 2.0, GREEN, true);
    Rect t = Rect(Point(3.0,3.0), 2.0, 2.0, PINK, true);
    Rect u = Rect(Point(3.0,1.0), 2.0, 2.0, PURPLE, true);
    win << r << s << t << u;
    win.output_buffer();
    return 0;
}
