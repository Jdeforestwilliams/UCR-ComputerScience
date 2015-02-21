#include "instinct.h"
int instinct_main()
{
    win.set_background_color(BLACK) ;

    Point p = point (5,5);

    line l = Line(Point(4,1), Point (7.9);

    l.set_color = (PURPLE);

    Circle c = Circle(Point(3,5),2 , RED);

    c.set_filled_in(true);

    Rect r = Rect(Point(7,2) 2, 4);

    Triangle t = Triangle Point(9,7), Point (8,8), Point(7,7);

    Message m = Message(Point(4,9), "John Smith");

    win << p << l << c << r << t << m;

    win.output_buffer();

    return 0;
}
