#ifndef GEOMETRY
#define GEOMETRY

#include <math.h>
#include <iostream>
#include <assert.h>


struct Point3D
{
	double x;
	double y;
	double z;
};


struct Vector3D
{
	Vector3D() = default;
  Vector3D(const Point3D& a, const Point3D& b) :
    x(b.x - a.x), y(b.y - a.y), z(b.z - a.z),
    start(a), end(b) {}
  Vector3D(double x, double y, double z) : x(x), y(y), z(z),
                                           end(Point3D{x, y, z}){}

  double x, y, z;
  Point3D start = {}; // initialize to zero from constructor with doubles
  Point3D end;

	double norm()
	{
		return std::sqrt(x*x + y*y + z*z);
	}
};

std::ostream& operator<<(std::ostream& output, const Point3D& p)
{
  output << "x= "<< p.x << " y= " << p.y << " z= " << p.z << "\n";
  return output;
}

std::ostream& operator<<(std::ostream& output, const Vector3D& p)
{
  output << "x= "<< p.x << " y= " << p.y << " z= " << p.z << "\n";
  return output;
}

Vector3D operator+(const Vector3D& a, const Vector3D& b)
{
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}

Vector3D operator*(const double s, const Vector3D& a)
{
  return {s * a.x, s * a.y, s * a.z};
}

Point3D operator+(const Point3D& A, const Vector3D& v)
{
  return {A.x + v.x, A.y + v.y, A.z + v.z}; // member initialization
}


template <typename Vector>
Vector cross(const Vector& v0, const Vector& v1)
{
	Vector v_res{};
	v_res.x = v0.y * v1.z - v1.y * v0.z;
	v_res.y = v0.z * v1.x - v0.x * v1.z;
	v_res.z = v0.x * v1.y - v1.x * v0.y;
	return v_res;
}

template <typename Vector>
double dot(const Vector& v0, const Vector& v1)
{
  return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}


Point3D projected_point(const Point3D& p, const Vector3D& b)
{
  // project a onto b
  Vector3D a{b.start, p};
  double s = dot(a, b) / (dot(b, b)); // dot(b,b) = |b|^2
  assert(s >=0 && s <= 1);
  return {b.start + s * b};
}

template <typename Point>
class Triangle
{
  using Vector = Vector3D;

public:
	Triangle(Point& p0, Point& p1, Point& p2) : p0(p0), p1(p1), p2(p2) {}

  // area = |n x n| / 2
	double area()
	{
		// cross two vectors, starting at p0
		Vector v0{p0, p1};
		Vector v1{p0, p2};
		Vector cp = cross(v0, v1);
		return cp.norm() / 2;
	}

  Vector normal()
  {
    Vector v0{p0, p1};
    Vector v1{p0, p2};
    return cross(v0, v1);
  }

  // static
  Point& a() {return p0;}
  Point& b() {return p1;}
  Point& c() {return p2;}

private:
	Point p0;
	Point p1;
	Point p2;
};

template <typename Point>
class Barycenter
{
  using Vector = Vector3D;

public:
  Barycenter(Triangle<Point>& t, Point& R) : t(t), R(R) {}

  // for testing
  void get_areas(double& sa, double& sb, double& sc)
  {
    Vector va{R, t.a()};
    Vector vb{R, t.b()};
    Vector vc{R, t.c()};
    Vector n1 = cross(va, vb);
    Vector n2 = cross(vb, vc);
    Vector n3 = cross(vc, va);

    sa = n1.norm() / 2.0;
    sb = n2.norm() / 2.0;
    sc = n3.norm() / 2.0;
  }

  void print_coords()
  {
    double u, v, w;
    calculate_coords(u, v, w);
    std::cout << "u= " << u << " v= " << v << " w= " << w << std::endl;
  }

  // todo: barycentric coords as class data

  double pab()
  {
    Vector va{R, t.a()};
    Vector vb{R, t.b()};
    return dot(t.normal(), cross(va, vb));
  }

  double pbc()
  {
    Vector vb{R, t.b()};
    Vector vc{R, t.c()};
    return dot(t.normal(), cross(vb, vc));
  }

  double pca()
  {
    Vector va{R, t.a()};
    Vector vc{R, t.c()};
    return dot(t.normal(), cross(vc, va));
  }


private:
  void calculate_signed_areas(double& rab, double& rbc, double& rca)
  {
    Vector va{R, t.a()};
    Vector vb{R, t.b()};
    Vector vc{R, t.c()};
    rab = dot(t.normal(), cross(va, vb));
    rbc = dot(t.normal(), cross(vb, vc));
    rca = dot(t.normal(), cross(vc, va));
  }

  void calculate_coords(double& u, double& v, double& w)
  {
    double sa, sb, sc;
    calculate_signed_areas(sa, sb, sc);
    double abc = sa + sb + sc;
    u = sa / abc;
    v = sb / abc;
    w = sc / abc;
  }


private:
  Triangle<Point> t;
  Point R;
};






#endif //GEOMETRY
