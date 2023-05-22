#include <iostream>
#include "Vector.h"

GeomVector::vector2f GeomVector::scalerProduct2D(float scalerValue, vector2f v2)
{
	float _x, _y;
	_x = scalerValue * v2[X];
	_y = scalerValue * v2[Y];
	return vector2f(_x, _y);
}

float GeomVector::crossProduct2D(vector2f v1, vector2f v2)
{
	return v1[X] * v2[Y] - v1[Y] * v2[X];
}

GeomVector::vector3f GeomVector::crossProduct3D(vector3f v1, vector3f v2)
{
	float _x, _y, _z;

	/*
	*  u(u1,u2,u3), v(v1,v2,v3)
		  x  y  z
		| u1 u2 u3 |
		| v1 v2 v3 |
		Cross product (u X v) = (u2 * v3 - u3 * v2)x + (u3 * v1 - u1 * v3)y + (u1 * v2 - u2 * v1)z;
	*/

	_x = v1[Y] * v2[Z] - v1[Z] * v2[Y];
	_y = v1[Z] * v2[X] - v1[X] * v2[Z];
	_z = v1[X] * v2[Y] - v1[Y] * v2[X];
	return vector3f(_x, _y, _z);
}

float GeomVector::scalerTripleProduct(vector3f v1, vector3f v2, vector3f v3)
{
	auto crossV23 = crossProduct3D(v2, v3);

	return dotProduct(v1, crossV23);
}