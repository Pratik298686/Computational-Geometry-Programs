#include "IGeometry.h"

void IGeometry :: setEntityName(string entityName)
{
	this->entityName = entityName;
}
string IGeometry :: getEntityName()
{
	return entityName;
}