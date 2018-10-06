#ifndef HELPER_FUNCTIONS
#define HELPER_FUNCTIONS

bool almost_equal(double a, double b)
{
  double eps = 1e-15;
  return (a < b + eps && a > b - eps) ? true : false;
}

template <typename T>
bool almost_equal(T a, T b)
{
  const double eps = 1e-15;
  return (a.x < b.x + eps && a.x > b.x - eps) &&
         (a.y < b.y + eps && a.y > b.y - eps) &&
         (a.z < b.z + eps && a.z > b.z - eps) ? true : false;
}


#endif // HELPER_FUNCTIONS

