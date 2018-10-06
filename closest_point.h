#ifndef CLOSEST_POINT
#define CLOSEST_POINT


#include "geometry.h"
#include <iostream>



bool is_on_CA_feature_region(Point3D& p, Triangle<Point3D>& t)
{
  using Vector = Vector3D;
  Vector CP{t.c(), p};
  Vector CA{t.c(), t.a()};
  Vector AP{t.a(), p};
  Vector AC{t.a(), t.c()};

  return (dot(CP, CA) > 0 && dot(AP, AC) > 0) ? true : false;
}

bool is_on_BC_feature_region(Point3D& p, Triangle<Point3D>& t)
{
  using Vector = Vector3D;
  Vector BP{t.b(), p};
  Vector BC{t.b(), t.c()};
  Vector CP{t.c(), p};
  Vector CB{t.c(), t.b()};

  return (dot(BP, BC) > 0 && dot(CP, CB) > 0) ? true : false;
}

bool is_on_AB_feature_region(Point3D& p, Triangle<Point3D>& t)
{
  using Vector = Vector3D;
  Vector AP{t.a(), p};
  Vector AB{t.a(), t.b()};
  Vector BP{t.b(), p};
  Vector BA{t.b(), t.a()};

  return (dot(AP, AB) > 0 && dot(BP, BA) > 0) ? true : false;
}

bool is_on_A_voronoi_region(Point3D& p, Triangle<Point3D>& t)
{
  using Vector = Vector3D;
  Vector AP{t.a(), p};
  Vector AB{t.a(), t.b()};
  Vector AC{t.a(), t.c()};

  return (dot(AP, AB) < 0 && dot(AP, AC) < 0) ? true : false;
}

bool is_on_B_voronoi_region(Point3D& p, Triangle<Point3D>& t)
{
  using Vector = Vector3D;
  Vector BP{t.b(), p};
  Vector BA{t.b(), t.a()};
  Vector BC{t.b(), t.c()};

  return (dot(BP, BA) < 0 && dot(BP, BC) < 0) ? true : false;
}

bool is_on_C_voronoi_region(Point3D& p, Triangle<Point3D>& t)
{
  using Vector = Vector3D;
  Vector CP{t.c(), p};
  Vector CB{t.c(), t.b()};
  Vector CA{t.c(), t.a()};

  return (dot(CP, CB) < 0 && dot(CP, CA) < 0) ? true : false;
}


template <typename Point>
Point closest_point_on_triangle(Point& p, Triangle<Point>& t)
{
  // check if in vertex voronoi region

  if(is_on_A_voronoi_region(p, t))
  {
    std::cout << "region A\n";
    return t.a();
  }

  if(is_on_B_voronoi_region(p, t))
  {
    std::cout << "region B\n";
    return t.b();
  }

  if(is_on_C_voronoi_region(p, t))
  {
    std::cout << "region C\n";
    return t.c();
  }

  // check if outside edge and in edge feature regions

  Barycenter<Point3D> barc{t, p};
  if(barc.pab() < 0 && is_on_AB_feature_region(p, t))
  {
    std::cout << "outside AB edge\n";
    Vector3D AB{t.a(), t.b()};
    return projected_point(p, AB);
  }

  if(barc.pbc() < 0 && is_on_BC_feature_region(p, t))
  {
    std::cout << "outside BC edge\n";
    Vector3D BC{t.b(), t.c()};
    return projected_point(p, BC);
  }

  if(barc.pca() < 0 && is_on_CA_feature_region(p, t))
  {
    std::cout << "outside CA edge\n";
    Vector3D CA{t.c(), t.a()};
    return projected_point(p, CA);
  }


  // must be inside
  barc.print_coords();
  return {}; // 0,0,0

}




#endif // CLOSEST_POINT








