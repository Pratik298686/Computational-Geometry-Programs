#include "Point.h"

Point :: Point() : x(0.0), y(0.0), IGeometry("Point") { }

Point :: Point(double x, double y) : x(x), y(y) { }

void Point::input()
{
	cout << "Enter Point Coordinate (X,Y) : ";
	cin >> x >> y;
}

void Point::display()
{
	cout << getEntityName() << " :- {X : " << x << " , Y : " << y << " }" << endl;
}

