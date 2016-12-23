#include "wrench.h"

Wrench::Wrench(double d, double w, double h)
{
	make_handle(d, w, h);
	make_head(d, w, h);
}

void Wrench::make_handle(double d, double w, double h)
{
	/* vertice v1 = std::make_tuple(-d / 2, h / 2, w / 4);
	vertice v2 = std::make_tuple(-d / 2, -h / 2, w / 4);
	vertice v3 = std::make_tuple(-d / 2, h / 2, -3* w / 4);
	make_triangle(v1, v2, v3);
	v1 = std::make_tuple(-d / 2, -h / 2, -3 * w / 4);
	make_triangle(v1, v2, v3);
	v2 = std::make_tuple(d / 2, - h / 2, -3 * w / 4);
	make_triangle(v1, v2, v3);
	v1 = std::make_tuple(d / 2, h / 2, -3 * w / 4);
	make_triangle(v1, v2, v3);
	v3 = std::make_tuple(d / 2, h / 2, w / 4);
	make_triangle(v1, v2, v3);
	v1 = std::make_tuple(-d / 2, -h / 2, w / 4);
	make_triangle(v1, v2, v3); */

	vertice v1 = std::make_tuple(-d / 2, h / 2, w / 4);
	vertice v2 = std::make_tuple(d / 2, h / 2, w / 4);
	vertice v3 = std::make_tuple(d / 2, h / 2, -3 * w / 4);
	std::vector<vertice> tmp;
	tmp.push_back(v1);
	tmp.push_back(v2);
	tmp.push_back(v3);
	make_triangle_mirror_y(v1, v2, v3);
	v2 = std::make_tuple(-d / 2, h / 2, -3 * w / 4);
	make_triangle_mirror_y(v1, v2, v3);
	tmp.push_back(v2);
	make_walls(tmp);
}

void Wrench::make_head(double d, double w, double h)
{
	double x = d*sqrt(3) / 2;
	double y = d/2;
	vertice v1 = std::make_tuple(-x, h / 2, w / 4);
	vertice v2 = std::make_tuple(x, h / 2, w / 4);
	vertice v3 = std::make_tuple(2*x, h / 2, w/4 +d/2);
	vertice v4 = std::make_tuple(2*x, h / 2, w/4+d);
	vertice v5 = std::make_tuple(x, h / 2, w/4+2*d);
	vertice v6 = std::make_tuple(x, h / 2, w/4+d);
	vertice v7 = std::make_tuple(0, h / 2, w/4+d/2);
	vertice v8 = std::make_tuple(-x, h / 2, w/4+d);
	vertice v9 = std::make_tuple(-x, h / 2, w/4+2*d);
	vertice v10 = std::make_tuple(-2*x, h / 2, w/4+d);
	vertice v11 = std::make_tuple(-2*x, h / 2, w/4+d/2);
	std::vector<vertice> tmp;
	tmp.push_back(v1);
	tmp.push_back(v2);
	tmp.push_back(v3);
	tmp.push_back(v4);
	tmp.push_back(v5);
	tmp.push_back(v6);
	tmp.push_back(v7);
	tmp.push_back(v8);
	tmp.push_back(v9);
	tmp.push_back(v10);
	tmp.push_back(v11);
	make_walls(tmp);
	make_triangle_mirror_y(v1,v2,v7);
	make_triangle_mirror_y(v2,v3,v7);
	make_triangle_mirror_y(v3,v6,v7);
	make_triangle_mirror_y(v3,v4,v6);
	make_triangle_mirror_y(v4,v5,v6);
	make_triangle_mirror_y(v1,v7,v11);
	make_triangle_mirror_y(v11,v7,v8);
	make_triangle_mirror_y(v11,v8,v10);
	make_triangle_mirror_y(v10,v8,v9);
}