#include <iostream>
#include "closest_point.h"
#include "helper_functions.h"

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
  assert(almost_equal(closest_point_on_triangle(p1, t), {2, 3, 0}));

  // edge region BC
  Point p2{2.5, 1.5, 0};
  assert(almost_equal(closest_point_on_triangle(p2, t), {2, 1.5, 0}));

  // edge region AB
  Point p3{1, -1, 0};
  assert(almost_equal(closest_point_on_triangle(p3, t), {1, 0, 0}));

  // edge region AC
  Point p4{-1, 1.5, 0};
  assert(almost_equal(closest_point_on_triangle(p4, t),
         {0.384615384615385, 0.576923076923077, 0}));

  // vertex region A
  Point p5{-1, -1, 0};
  std::cout << closest_point_on_triangle(p5, t) << "\n";
  assert(almost_equal(closest_point_on_triangle(p5, t), {0, 0, 0}));

  // vertex region B
  Point p6{4, -4, 0};
  assert(almost_equal(closest_point_on_triangle(p6, t), {2, 0, 0}));
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
  assert(almost_equal(closest_point_on_triangle(p1, t), {1, 1, 1}));

  // edge region BC
  Point p2{2.5, 1.5, -1};
  assert(almost_equal(closest_point_on_triangle(p2, t),
                      {1.833333333333333, 0.1666666666666667, -0.6666666666666667}));

  // edge region AB
  Point p3{1, -1, -1};
  assert(almost_equal(closest_point_on_triangle(p3, t), {1.2, 0, -0.6}));

  // edge region AC
  Point p4{-1, 1.5, 0.1};
  assert(almost_equal(closest_point_on_triangle(p4, t), {0.2, 0.2, 0.2}));

  // vertex region A
  Point p5{-1, -1, 100};
  assert(almost_equal(closest_point_on_triangle(p5, t), {1, 1, 1}));

  // vertex region B
  Point p6{4, -4, -100};
  assert(almost_equal(closest_point_on_triangle(p6, t), {2, 0, -1}));
}


int main()
{
  test_closest_point();
  test_closest_points();
  test_closest_points_z();
  return 0;
}
