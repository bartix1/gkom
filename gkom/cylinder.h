#pragma once

#include "object.h"

class Cylinder : public Object
{
public:
	Cylinder() {};
	Cylinder(int n, double d, double h);
	void connect_walls(std::vector<vertice> circle);
protected:
	std::vector<vertice> make_circle(int n, double d, double h);

};