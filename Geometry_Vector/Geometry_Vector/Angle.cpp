#include "Angle.h"
#include "Vector.h"

template<class T, size_t dim>
float getAngle(GeomVector::Vector<T, dim> v1, GeomVector::Vector<T, dim> v2)
{
    auto dot = dotProduct(v1, v2);
    auto theta = acos(fabs(dot));

    return RadianceToDegree(theta);
}

float GeomVector::AngleLine2d(const Line2d& l1, const Line2d& l2)
{
    return getAngle(l1.getDir(), l2.getDir());
}

float GeomVector::AngleLine3d(const Line3d& l1, const Line3d& l2)
{
    return getAngle(l1.getDir(), l2.getDir());
}

float GeomVector::AngleLinePlane(const Line3d& l1, const Planef& p)
{
    float angle = getAngle(l1.getDir(), p.getNormal());

    return 90 - angle;
}

float GeomVector::AnglePlanes(const Planef& p1, const Planef& p2)
{
    return getAngle(p1.getNormal(), p2.getNormal());
}



/*
float GeomVector::AngleLine2d(const Line2d& l1, const Line2d& l2)
{
    auto dot = dotProduct(l1.getDir(), l2.getDir());
    auto theta = acos(fabs(dot));

    return RadianceToDegree(theta);
}

float GeomVector::AngleLine3d(const Line3d& l1, const Line3d& l2)
{
    auto dot = dotProduct(l1.getDir(), l2.getDir());
    auto theta = acos(fabs(dot));

    return RadianceToDegree(theta);
}

float GeomVector::AngleLinePlane(const Line3d& l1, const Planef& p )
{
    auto dot = dotProduct(l1.getDir(), p.getNormal());

    float theta = acos(fabs(dot));

    float angle = RadianceToDegree(theta);

    return 90 - angle;
}

*/