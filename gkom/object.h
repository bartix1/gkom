#pragma once

#include <vector>
#include <tuple>
#include <cmath>

typedef std::tuple<double, double, double> vertice;

class Object
{
public:
	std::vector<vertice> vert_vector;

	Object() {};
	double distance(vertice v1, vertice v2, vertice v3);

protected:
	void make_triangle_mirror_y(vertice v1, vertice v2, vertice v3);
	void make_triangle(vertice v1, vertice v2, vertice v3);
	void make_walls(std::vector<vertice>);
};