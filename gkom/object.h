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
	double distance(vertice v1, vertice v2, vertice v3); //distace

protected:
	void make_triangle_mirror_y(vertice v1, vertice v2, vertice v3); //add 6 vertices (2 triangles with opposite y) to vert_vector 
	void make_triangle(vertice v1, vertice v2, vertice v3);	//add 3 vertices (triangle) to vert_vector
	void make_walls(std::vector<vertice>); // create walls between one plane and its y mirror plane
};