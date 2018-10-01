#include "geometry.h"

int main()
{

  Point2D a{0, 1};
  Point2D b{-2, 3.1};

  Vector2D<Point2D> v0{a,b};
  std::cout << v0.x << " " << v0.y << '\n';


  return 0;
}
