#ifndef _POINT_H
#define _POINT_H
#include "IGeometry.h"
using namespace std;
class DLLEXPORT Point : public IGeometry
{
private:
	double x, y;
public:
	Point();
	Point(double x, double y);

	void input();
	void display();
};
#endif
