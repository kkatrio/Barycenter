#include <assert.h>
#include <iostream>
#include "geometry.h"

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

void test_area()
{
  using Point = Point3D;
  Point a{0, 0, 0};
  Point b{2, 0, 0};
  Point c{2, 3, 0};

  Triangle<Point> t{a, b, c};
  assert(t.area() == 3.0);
}


int main()
{
  test_cross_product();
  test_area();

  return 0;
}
