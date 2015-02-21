#include "instinct.h"
#include <stdlib.h>
#include <cmath>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 800;
const int FRAME_PERIOD = 10;
const double PI = 3.1415;
const double LEFT_EDGE = 0.0;
const double BOTTOM_EDGE = 0.0;
const double TOP_EDGE = 1000.0;
const double RIGHT_EDGE = 1000.0;
const double MOUSE_RADIUS = 100.0;
const double PRECISION_MAX = 100000.0;

/*
 * Returns a random integer from start to end inclusive
 */
int rand_range(int start, int end)
{
  return start + rand() % (start+end);
}

/*
 * Returns the magnitude from (x1, y1) to (x2, y2) on a 2D-coordinate plane
 */
double magnitude(const double & x1, const double & y1, 
					  const double x2, const double y2)
{
    double magnitude;
    magnitude = sqrt(((x1 - x2)*(x1-x2))+((y1-y2)*(y1-y2)));
    return magnitude;
}

/*
 * Returns true whether the Point p is inside the Circle c
 */
bool is_inside(const Point & p, const Circle & c)
{
  if (magnitude(p.get_x(), p.get_y(), c.get_center.get_x(),
        c.get_center.get_y) <= c.get_radius())
    {
        return true;
    }
    else
    return false;
}

/*
 * Output all the Points to win in vector v only if it is inside Circle c
 */
void output_in_circle(const vector<Point> & v, const Circle & c)
{
  for(int i = 0; i < v.size(); i++)
    {
        win << v.at(i);
    }
}

/*
 * Returns the number of Points in vector v that are inside the Circle c
 */
int count_in_circle(const vector<Point> & v, const Circle & c)
{
  int total = 0;
  return total;
}

/*
 * Returns a Point object with a random location in the coordinate plane
 * with a precision of 5 decimal places
 */
Point random_point()
{
  double x = rand_range((int)LEFT_EDGE, (int)RIGHT_EDGE) + 
			 	 rand_range(0, (int)PRECISION_MAX - 1) / PRECISION_MAX;
  double y = rand_range((int)BOTTOM_EDGE, (int)TOP_EDGE) + 
				 rand_range(0, (int)PRECISION_MAX - 1) / PRECISION_MAX;
  return Point(x, y, BLACK, true);
}

/*
 * Adds randomly generated points to vector v up to num_points
 */
void add_random_points(vector<Point> & v, int num_points)
{
  return;
}

void move_randomly(vector<Point> & v)
{
; 
}

int instinct_main()
{
  //Initialize defaults
  srand(time(NULL));
  win.set_window_size(WINDOW_WIDTH, WINDOW_HEIGHT);
  win.coord(LEFT_EDGE, BOTTOM_EDGE, RIGHT_EDGE, TOP_EDGE);
  win.set_background_color(BLACK);

  //Initialize vector of random Points
  const int MINPOINTS = 100;
  const int MAXPOINTS = 200;
  vector<Point> v;
  add_random_points(v, rand_range(MINPOINTS, MAXPOINTS));
  
  //Initialize Circle following mouse;
  Circle mouse_circle = Circle(win.get_mouse_loc(), MOUSE_RADIUS, WHITE, true);

  //Initialize Counters
  const double MESSAGE_COUNT_POSX = 900.0;
  const double MESSAGE_COUNT_POSY1 = 900.0;
  const double MESSAGE_COUNT_POSY2 = 850.0;
  int current_count = 0;
  int total_count = 0;

  Timer prg;
  prg.start();
  while (!win.is_key_down("esc")) //Stop the animating loop with escape key
  {
	 win.clear_buffer();
	 
    //Set the center of the circle to mouse location
	 mouse_circle.set_center(win.get_mouse_loc()); 

	 //Randomly move the points
	 move_randomly(v);

	 //Update the number of points seen in the mouse circle
	 current_count = count_in_circle(v, mouse_circle);
	 if (current_count > total_count)
		total_count = current_count;

	 //Output everything
    win << mouse_circle;
	 output_in_circle(v, mouse_circle);
	 win << Message(Point(MESSAGE_COUNT_POSX, MESSAGE_COUNT_POSY1), current_count, RED);
	 win << Message(Point(MESSAGE_COUNT_POSX, MESSAGE_COUNT_POSY2), total_count, YELLOW);
    win.output_buffer();

	 //Always wait a same number of milliseconds each loop
    wait_for(FRAME_PERIOD - prg.get_time());
    prg.reset();
  }

  return 0;
}
