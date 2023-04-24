#ifndef _IGEOMETRY_H
#define _IGEOMETRY_H

#include <iostream>
#include <string>
using namespace std;
class IGeometry
{
private:
	string entityName;
public:
	 IGeometry(){}
	 IGeometry(string entityName) : entityName(entityName){}

	virtual void input() = 0;
	virtual void display() = 0;

	void setEntityName(string entityName);

	string getEntityName();

};

#endif
