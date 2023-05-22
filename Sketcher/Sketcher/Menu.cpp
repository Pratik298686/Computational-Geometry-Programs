#include <iostream>
#include <vector>
#include "IGeometry.h"
#include "Menu.h"
#include "Line.h"
#include "Point.h"
#include "Circle.h"


int Menu::ShowMenu(vector<IGeometry*>& geometry)
{
	unsigned int choice;
	cout << "Enter Choice: " << endl;
	cout << "1. Point input " << endl;
	cout << "2. Line input " << endl;
	cout << "3. Circle input " << endl;
	cout << "4. Display " << endl;
	cout << "Exit : Enter Anything " << endl;

	cin >> choice;

	switch (choice)
	{
	case 1:
	{
		IGeometry* pt = new Point();
		pt->input();
		//(*pt).input();
		geometry.push_back(pt);
	}
	case 2:
	{
		IGeometry* line = new Line();
		line->input();
		geometry.push_back(line);
	}
	case 3:
	{
		IGeometry* circle = new Circle();
		circle->input();
		geometry.push_back(circle);
	}
	case 4:
	{
		for (auto it : geometry)
		{
			it->display();
		}
	}
	default:
		break;
	}
	return 0;
}