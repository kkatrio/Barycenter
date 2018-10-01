#include <iostream>

struct Point2D
{
	double x;
	double y;
};

template <typename Point>
struct Vector2D
{
	Vector2D(Point& a, Point& b) : x(b.x - a.x), y(b.y - a.y) {}

	double x;
	double y;
};




template <typename Point>
class Triangle
{
public:
	Triangle(Point& p0, Point& p1, Point& p2) : p0(p0), p1(p1), p2(p2) {}

/*
	area()
	{

	}
*/



private:
	Point p0;
	Point p1;
	Point p2;
};
