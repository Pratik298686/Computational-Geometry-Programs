#include <iostream>
#include <vector>
//#include "IGeometry.h"
#include "Menu.h"
using namespace std;

int main()
{
	cout << "Welcome to Sketcher App: \n";
	vector<IGeometry*> geometry;

	Menu menu;
	unsigned int input = 0;

	do {
		input = menu.ShowMenu(geometry);
	} while (input != -1);


}