#include "geometry.h"
#include "closest_point.h"

#include <assert.h>
#include <iostream>


void test_cross_product()
{
  using Point = Point3D;
  using Vector = Vector3D;
  Point o{0, 0, 0};
  Point a{2, 0, 0};
  Point b{2, 3, 2};
  Vector v0{o, a};
  Vector v1{o, b};
  Vector cp = cross(v0, v1);

  Vector v{0, -4, 6};
  assert(cp == v);
}

void test_dot_product()
{
  using Vector = Vector3D;
  Vector a{2, 0, 0};
  Vector b{2, 3, 2};
  // to fix
  assert(dot(a, b) == 4);
} 

void test_area()
{
  using Point = Point3D;
  Point a{0, 0, 0};
  Point b{2, 0, 0};
  Point c{2, 3, 0};

  Triangle<Point> t{a, b, c};
  assert(t.area() == 3.0);
}

bool almost_equal(double a, double b)
{ 
  double eps = 1e-10;
  return (a < b + eps && a > b - eps) ? true : false;
}

void test_signed_areas()
{
  using Point = Point3D;
  Point a{0, 0, 0};
  Point b{2, 0, 0};
  Point c{2, 3, 0};
  // get a triangle
  Triangle<Point> t{a, b, c};
  // get a query point R
  Point R{1.5, 1.5, 0};

  Barycenter<Point> brc{t, R};
  double sa, sb, sc;
  brc.get_areas(sa, sb, sc);

  std::cout << sa + sb + sc << " " << t.area() << std::endl;
  assert(almost_equal(sa + sb + sc, t.area()));
}

void test_coords()
{
  using Point = Point3D;
  Point a{0, 0, 0};
  Point b{2, 0, 0};
  Point c{2, 3, 0};
  Triangle<Point> t{a, b, c};
  Point R{1.5, 1.5, 0};
  Barycenter<Point> brc{t, R};
  brc.print_coords(); 
}

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

int main()
{
  test_cross_product();
  test_area();
  test_dot_product();
  test_signed_areas();
  test_coords();
  test_closest_point();

  return 0;
}
