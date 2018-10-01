#include <math.h>

struct Point3D
{
	double x;
	double y;
	double z;
};

struct Vector3D
{
	Vector3D() = default;
	Vector3D(Point3D& a, Point3D& b) : x(b.x - a.x), y(b.y - a.y), z(b.z - a.z) {}
	Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

	double x;
	double y;
	double z;

	double norm()
	{
		return std::sqrt(x*x + y*y + z*z);
	}

	bool operator==(const Vector3D v)
	{
		return (v.x == x && v.y == y && v.z == z) ? true : false;
	}
};

template <typename Vector>
Vector cross(const Vector& v0, const Vector& v1)
{
	Vector v_res{};
	v_res.x = v0.y * v1.z - v1.y * v0.z;
	v_res.y = v0.z * v1.x - v0.x * v1.z;
	v_res.z = v0.x * v1.y - v1.x * v0.y;
	return v_res;
}

template <typename Point>
class Triangle
{
public:
	Triangle(Point& p0, Point& p1, Point& p2) : p0(p0), p1(p1), p2(p2) {}

	double area()
	{
		// cross two vectors, starting at p0
		Vector3D v0{p0, p1};
		Vector3D v1{p0, p2};
		Vector3D cp = cross(v0, v1);
		return cp.norm() / 2;
	}

private:
	Point p0;
	Point p1;
	Point p2;
};
