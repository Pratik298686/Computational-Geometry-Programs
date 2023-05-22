#ifndef _CORE_H
#define _CORE_H

#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>

namespace GeomVector
{
#define TOLERANCE 0.0000001
#define ZERO 0

	enum RELATIVE_POSITION
	{
		LEFT, RIGHT, BEHIND, BEYOND, BETWEEN, ORIGIN, DESTINATION
	};

	static bool isEqualD(double x, double y)
	{
		return fabs(x - y) < TOLERANCE;
	}

	static bool _xor(bool x, bool y)
	{
		return x ^ y;
	}

	float RadianceToDegree(float theta)
	{
		return theta * (180 / M_PI);
	}
}


#endif // !_CORE_H




