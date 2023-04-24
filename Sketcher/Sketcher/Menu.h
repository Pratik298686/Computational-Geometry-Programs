#ifndef _MENU_H
#define _MENU_H
#include "IGeometry.h"
#include <vector>
using namespace std;
class Menu
{
public:
	int ShowMenu(vector<IGeometry*>& geometry1);
};
#endif
