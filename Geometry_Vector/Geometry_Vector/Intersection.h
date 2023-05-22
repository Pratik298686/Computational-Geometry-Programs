#ifndef _INTERSECTION_H
#define _INTERSECTION_H

#include <iostream>
#include "Point.h"
#include "Line.h"
#include "Plane.h"

namespace GeomVector
{
	bool Intersection(const Point2d&, const Point2d&, const Point2d&, const Point2d&);

	bool Intersection(const Point2d&, const Point2d&, const Point2d&, const Point2d&, Point2d&);

	bool Intersection(const Line2d&, const Line2d&, Point2d);

	bool Intersection(const Line3d& line, const Planef& plane, Point3d& point);

	bool intersect(const Planef& plane1, const Planef& plane2, Line3d& line);
}
#endif // !_INTERSECTION_H

