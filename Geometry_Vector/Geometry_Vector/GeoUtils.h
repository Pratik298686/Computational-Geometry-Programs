#ifndef _GEOUTILS_H
#define _GEOUTILS_H

#include <iostream>
#include <vector>
#include "Point.h"

namespace GeomVector
{
	double areaTriangle2D(const Point2d& a, const Point2d& b, const Point2d& c);

	int orientation2D(const Point2d& a, const Point2d& b, const Point2d& c);

	bool collinear(const vector3f& v1, const vector3f& v2);

	bool collinear(const Point3d& a, const Point3d& b, const Point3d& c);

	bool coplaner(const vector3f& v1, const vector3f& v2, const vector3f& v3);

	bool coplaner(const Point3d& a, const Point3d& b, const Point3d& c, const Point3d& d);
}

#endif // !_GEOUTILS_H

