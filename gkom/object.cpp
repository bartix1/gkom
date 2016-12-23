#include "object.h"

void Object::make_triangle(vertice v1, vertice v2, vertice v3)
{
	vert_vector.push_back(v1);
	vert_vector.push_back(v2);
	vert_vector.push_back(v3);
}

void Object::make_triangle_mirror_y(vertice v1, vertice v2, vertice v3)
{
	make_triangle(v1, v2, v3);
	v1 = std::make_tuple(std::get<0>(v1), -std::get<1>(v1), std::get<2>(v1));
	v2 = std::make_tuple(std::get<0>(v2), -std::get<1>(v2), std::get<2>(v2));
	v3 = std::make_tuple(std::get<0>(v3), -std::get<1>(v3), std::get<2>(v3));
	make_triangle(v1, v2, v3);
}

double Object::distance(vertice v1, vertice v2, vertice v3)
{
	double x1 = std::get<0>(v1);
	double y1 = std::get<1>(v1);
	double z1 = std::get<2>(v1);
	double x2 = std::get<0>(v2);
	double y2 = std::get<1>(v2);
	double z2 = std::get<2>(v2);
	double x3 = std::get<0>(v3);
	double y3 = std::get<1>(v3);
	double z3 = std::get<2>(v3);
	double dist = sqrt(pow((x3 - x1), 2) + pow((y3 - y1), 2) + pow((z3 - z1), 2)) + sqrt(pow((x3 - x2), 2) + pow((y3 - y2), 2) + pow((z3 - z2), 2));
	return dist;
}

void Object::make_walls(std::vector<vertice> circle)
{
	vertice v1, v2, v3;
	for (unsigned i = 0; i < circle.size(); i++)
	{
		v1 = circle[i];
		v2 = circle[(i + 1) % circle.size()];
		v3 = std::make_tuple(std::get<0>(v1), -std::get<1>(v1), std::get<2>(v1));
		make_triangle(v1, v2, v3);
		v1 = std::make_tuple(std::get<0>(v2), -std::get<1>(v2), std::get<2>(v2));
		make_triangle(v1, v2, v3);
	}
}