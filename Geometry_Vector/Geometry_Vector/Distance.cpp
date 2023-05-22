#include "Distance.h"
#include "Vector.h"

float GeomVector::Distance(Line3d& l1, Point3d& p1)
{
    auto AC = p1 - l1.getPoint();
    auto t = dotProduct(l1.getDir(), AC);
    auto xt = l1.getPoint() + l1.getDir() * t;
    auto dist_vec = xt - p1;

    return dist_vec.magnitude();
}

float GeomVector::Distance(Planef& p, Point3d& Q)
{
    auto result = dotProduct(p.getNormal(), Q) - p.getD();

    return result;
}