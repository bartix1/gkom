#include "cylinder.h"


Cylinder::Cylinder(int n, double d, double h)
{
	std::vector<vertice> circle = make_circle(n, d, h);
	make_walls(circle);
	connect_walls(circle);
}

std::vector<vertice> Cylinder::make_circle(int n, double d, double h)
{
	vertice vertex;
	double PI = 3.1415;
	std::vector<vertice> circle;
	double delta = 360.0 / n;
	for (int i = 0; i < n; ++i)
	{
		double theta = double(i)*delta;
		double next_theta = double(i + 1)*delta;
		vertex = std::make_tuple(d*cos(theta*PI / 180.0), h / 2, -d*sin(theta*PI / 180.0));
		circle.push_back(vertex);
	}
	return circle;
}

void Cylinder::connect_walls(std::vector<vertice> circle)
{
	vertice v1, v2, v3;
	for (unsigned i = 0; i < circle.size(); i++)
	{
		v1 = circle[i];
		v2 = circle[(i + 1) % circle.size()];
		v3 = std::make_tuple(0.0, std::get<1>(v1), 0.0);
		make_triangle_mirror_y(v1, v2, v3);
	}
}