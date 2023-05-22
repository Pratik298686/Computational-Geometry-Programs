#include <iostream>
#include "Vector.h"
#include "GeoUtils.h"
#include "Point.h"
#include "Line.h"

using namespace GeomVector;

int main()
{
	GeomVector::Vector<float, 2> vec1(1.0f, 2.0f);
	GeomVector::Vector<float, 2> vec2(3.0f, 4.0f);

	std::cout << crossProduct2D(vec1, vec2) << std::endl;

	GeomVector::Point2d p1(10.0f, 1.0f);
	GeomVector::Point2d p2(3.0f, 8.0f);
	GeomVector::Point2d p3(8.0f, 5.0f);

	auto ar = GeomVector::areaTriangle2D(p1, p2, p3);
	std::cout << ar << std::endl;

	auto orientation = GeomVector::orientation2D(p1, p2, p3);
	std::cout << orientation << std::endl;

	GeomVector::Vector<float, 2> p4(10.0f, 1.0f);
	GeomVector::Vector<float, 2> p5(3.0f, 8.0f);

	GeomVector::Line<float, DIM2> line(p4, p5);

	auto dir = line.getDir();
	std::cout << dir[0] << " , " << dir[1] << std::endl;

	auto pt = line.getPoint();
	std::cout << pt[0] << " , " << pt[1] << std::endl;


}