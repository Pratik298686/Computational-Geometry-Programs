#ifndef  _PLANE_H
#define _PLANE_H

#include <iostream>
#include "Vector.h"
#include "Point.h"

namespace GeomVector
{
	template<class coordinate_type>
	class Plane
	{
		vector3f normal;
		float d = 0;

	public:
		Plane() {}

		Plane(vector3f& _normal, float _constant) : normal(_normal), d(_constant) {
			normal.normalize();
		}

		Plane(Point3d& p1, Point3d& p2, Point3d& p3)
		{
			auto P12 = p2 - p1;
			auto P13 = p3 - p1;

			normal = crossProduct3D(P12, P13);
			normal.normalize();
			d = dotProduct(normal, p1);
		}

		vector3f getNormal() const
		{
			return normal;
		}

		float getD() const
		{
			return d;
		}
	};

	typedef Plane<float> Planef;
}

#endif // ! _PLANE_H

