#include <iostream>
#include "closest_point.h"


void test_closest_point()
{
  using Point = Point3D;
  Point a{0, 0, 0};
  Point b{2, 0, 0};
  Point c{2, 3, 0};
  Triangle<Point> t{a, b, c};
  Point p{1.5, 1.5, 0};
  closest_point_on_triangle(p, t);
}

void test_closest_points()
{
  using Point = Point3D;
  Point a{0, 0, 0};
  Point b{2, 0, 0};
  Point c{2, 3, 0};
  Triangle<Point> t{a, b, c};

  // vertex region C
  Point p1{2.5, 3.5, 0};
  std::cout << closest_point_on_triangle(p1, t) << "\n";

  // edge region BC
  Point p2{2.5, 1.5, 0};
  std::cout << closest_point_on_triangle(p2, t) << "\n";

  // edge region AB
  Point p3{1, -1, 0};
  std::cout << closest_point_on_triangle(p3, t) << "\n";

  // edge region AC
  Point p4{-1, 1.5, 0};
  std::cout << closest_point_on_triangle(p4, t) << "\n";

  // vertex region A
  Point p5{-1, -1, 0};
  std::cout << closest_point_on_triangle(p5, t) << "\n";

  // vertex region B
  Point p6{4, -4, 0};
  std::cout << closest_point_on_triangle(p6, t) << "\n";
}

void test_closest_points_z()
{
  using Point = Point3D;
  Point a{0, 0, 0};
  Point b{2, 0, -1};
  Point c{1, 1, 1};
  Triangle<Point> t{a, b, c};

  // vertex region C
  Point p1{1.5, 3.5, 4};
  std::cout << closest_point_on_triangle(p1, t) << "\n";

  // edge region BC
  Point p2{2.5, 1.5, -1};
  std::cout << closest_point_on_triangle(p2, t) << "\n";

  // edge region AB
  Point p3{1, -1, -1};
  std::cout << closest_point_on_triangle(p3, t) << "\n";

  // edge region AC
  Point p4{-1, 1.5, 0.1};
  std::cout << closest_point_on_triangle(p4, t) << "\n";

  // vertex region A
  Point p5{-1, -1, 100};
  std::cout << closest_point_on_triangle(p5, t) << "\n";

  // vertex region B
  Point p6{4, -4, -100};
  std::cout << closest_point_on_triangle(p6, t) << "\n";
}


int main()
{
  test_closest_point();
  test_closest_points();
  std::cout << "\n";
  test_closest_points_z();
  return 0;
}
