#ifndef _LINE_H
#define _LINE_H

#include <iostream>
#include "Vector.h"
#include "Point.h"

namespace GeomVector
{
	template<class coordinate_type, size_t dimension>
	class Line
	{
		Vector<coordinate_type, dimension> dir;
		Vector<coordinate_type, dimension> point;

	public:
		Line() {}

		Line(Vector<coordinate_type, dimension>& p1, Vector<coordinate_type, dimension>& p2)
		{
			point = p1;
			dir = p2 - p1;
			dir.normalize();
		}

		void setDir(Vector<coordinate_type, dimension>&);

		void setPoint(Vector<coordinate_type, dimension>&);

		Vector<coordinate_type, dimension> getPoint() const;

		Vector<coordinate_type, dimension> getDir() const;
	};

	typedef Line<float, DIM2> Line2d;
	typedef Line<float, DIM3> Line3d;

	template<class coordinate_type, size_t dimension>
	inline void Line<coordinate_type, dimension>::setDir(Vector<coordinate_type, dimension>& dir)
	{
		dir.assign(X, dir[X]);
		dir.assign(Y, dir[Y]);
		dir.assign(Z, dir[Z]);
	}

	template<class coordinate_type, size_t dimension>
	inline void Line<coordinate_type, dimension>::setPoint(Vector<coordinate_type, dimension>& point)
	{
		point.assign(X, point[X]);
		point.assign(Y, point[Y]);
		point.assign(Z, point[Z]);
	}

	template<class coordinate_type, size_t dimension>
	inline Vector<coordinate_type, dimension> Line<coordinate_type, dimension>::getPoint() const
	{
		return point;
	}

	template<class coordinate_type, size_t dimension>
	inline Vector<coordinate_type, dimension> Line<coordinate_type, dimension>::getDir() const
	{
		return dir;
	}
}

#endif // !_LINE_H

