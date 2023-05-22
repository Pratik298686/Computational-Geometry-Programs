#include "Intersection.h"
#include "GeoUtils.h"
#include "Core.h"

bool GeomVector::Intersection(const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d)
{
	auto ab_c = orientation2D(a, b, c);
	auto ab_d = orientation2D(a, b, d);
	auto cd_a = orientation2D(c, d, a);
	auto cd_b = orientation2D(c, d, b);

	if (ab_c == RELATIVE_POSITION::BETWEEN || ab_c == RELATIVE_POSITION::ORIGIN || ab_c == RELATIVE_POSITION::DESTINATION
		|| ab_d == RELATIVE_POSITION::BETWEEN || ab_d == RELATIVE_POSITION::ORIGIN || ab_d == RELATIVE_POSITION::DESTINATION
		|| cd_a == RELATIVE_POSITION::BETWEEN || cd_a == RELATIVE_POSITION::ORIGIN || cd_a == RELATIVE_POSITION::DESTINATION
		|| cd_b == RELATIVE_POSITION::BETWEEN || cd_b == RELATIVE_POSITION::ORIGIN || cd_b == RELATIVE_POSITION::DESTINATION)
	{
		return true;
	}

	return _xor(ab_c == RELATIVE_POSITION::LEFT, ab_d == RELATIVE_POSITION::LEFT) &&
		_xor(cd_a == RELATIVE_POSITION::LEFT, cd_b == RELATIVE_POSITION::LEFT);
}

bool GeomVector::Intersection(const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d, Point2d& intersectionPoint)
{
	vector2f AB = b - a;
	vector2f CD = c - d;

	vector2f n(CD[Y], -CD[X]);

	auto deno = dotProduct(n, AB);

	if (!isEqualD(deno, ZERO))
	{
		vector2f AC = c - a;

		auto num = dotProduct(n, AC);

		auto t = num / deno;

		auto x = a[X] + t * AB[X];
		auto y = a[X] + t * AB[Y];

		intersectionPoint.assign(X, x);
		intersectionPoint.assign(Y, y);

		return true;
	}
	else
	{
		return false;
	}
}

bool GeomVector::Intersection(const Line2d& l1, const Line2d& l2, Point2d intersectionPoint)
{
	auto l1_start = l1.getPoint();
	auto l1_end = l1_start + l1.getDir();
	auto l2_start = l2.getPoint();
	auto l2_end = l2_start + l2.getDir();

	return Intersection(l1_start, l1_end, l2_start, l2_end, intersectionPoint);
}

bool GeomVector::Intersection(const Line3d& line, const Planef& plane, Point3d& point)
{
	auto n = plane.getNormal();
	auto D = plane.getD();
	auto d = line.getDir();
	auto p = line.getPoint();

	auto nd = dotProduct(n, d);

	if (!isEqualD(nd, ZERO))
	{
		auto t = (-1 * dotProduct(n, p) + D) / nd;
		point.assign(X, p[X] + t * d[X]);
		point.assign(Y, p[Y] + t * d[Y]);
		point.assign(Z, p[Z] + t * d[Z]);

		return true;
	}
	else
		return false;
	return false;
}

bool GeomVector::intersect(const Planef& plane1, const Planef& plane2, Line3d& line)
{
	auto n1 = plane1.getNormal();
	auto n2 = plane2.getNormal();
	auto d1 = plane1.getD();
	auto d2 = plane2.getD();

	auto direction = crossProduct3D(n1, n2);

	if (isEqualD(direction.magnitude(), ZERO))
		return false;

	auto n1n2 = dotProduct(n1, n2);
	auto n1n2_2 = n1n2 * n1n2;

	auto a = (d2 * n1n2 - d1) / (n1n2_2 - 1);
	auto b = (d1 * n1n2 - d2) / (n1n2_2 - 1);

	auto point = n1 * a + n2 * b;

	line.setPoint(point);
	direction.normalize();

	line.setDir(direction);

	return true;
}