#pragma once
#include "cylinder.h"

class Nut : public Cylinder
{
public:
	Nut(int inner_n = 24, float inner_d = 0.5, int outer_n = 6, float outer_d = 1, float height = 1);
	
private:
	void connect_circles(std::vector<vertice> in, std::vector<vertice> out); // connect outer cylinder with inner
	void connect_one(std::vector<vertice> in, std::vector<vertice> out); 
};