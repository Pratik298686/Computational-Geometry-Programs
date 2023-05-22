#ifndef _DISTANCE_H
#define _DISTANCE_H

#include <iostream>
#include "Line.h"
#include "Point.h"
#include "Plane.h"

namespace GeomVector
{
	float Distance(Line3d& l1, Point3d& p1);

	float Distance(Planef& p, Point3d& Q);
}

#endif // !_DISTANCE_H

