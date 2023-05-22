#include <iostream>
#include <math.h>
#include <algorithm>

#include "GeoUtils.h"
#include "Core.h"
#include "Point.h"

using namespace GeomVector;

double GeomVector::areaTriangle2D(const Point2d& a, const Point2d& b, const Point2d& c)
{
	auto AB = b - a;
	auto AC = c - a;

	// This will give area of parallelogram
	float area = GeomVector::crossProduct2D(AB, AC);

	return area / 2;
}

int GeomVector::orientation2D(const Point2d& a, const Point2d& b, const Point2d& c)
{
	double area = areaTriangle2D(a, b, c);

	if (area > 0 && area < TOLERANCE)
		area = 0;
	if (area < 0 && area > TOLERANCE)
		area = 0;

	GeomVector::vector2f ab = b - a;
	GeomVector::vector2f ac = c - a;

	if (area > 0)
		return int(RELATIVE_POSITION::LEFT);

	if (area < 0)
		return int(RELATIVE_POSITION::RIGHT);

	if (ab[X] * ac[X] < 0 || ab[Y] * ac[Y] < 0)
		return int(RELATIVE_POSITION::BEHIND);

	if (ab.magnitude() < ac.magnitude())
		return int(RELATIVE_POSITION::BEYOND);
	if (a == c)
		return int(RELATIVE_POSITION::ORIGIN);

	if (a == b)
		return int(RELATIVE_POSITION::DESTINATION);

	return int(RELATIVE_POSITION::BETWEEN);
}

bool GeomVector::collinear(const vector3f& v1, const vector3f& v2)
{
	auto a = v1[X] * v2[Y] - v1[Y] * v2[X];
	auto b = v1[Y] * v2[Z] - v2[Z] * v1[Y];
	auto c = v1[X] * v2[Z] - v1[Z] * v2[X];

	return isEqualD(a, ZERO) && isEqualD(b, ZERO) && isEqualD(c, ZERO);
}

bool GeomVector::collinear(const Point3d& a, const Point3d& b, const Point3d& c)
{
	auto AB = b - a;
	auto AC = c - a;
	return collinear(AB, AC);
}

bool GeomVector::coplaner(const vector3f& v1, const vector3f& v2, const vector3f& v3)
{
	float value = scalerTripleProduct(v1, v2, v3);

	return isEqualD(value, ZERO);
}

bool GeomVector::coplaner(const Point3d& a, const Point3d& b, const Point3d& c, const Point3d& d)
{
	auto AB = b - a;
	auto AC = c - a;
	auto AD = d - a;

	return coplaner(AB, AC, AD);
}