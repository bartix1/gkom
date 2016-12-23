#include "nut.h"

Nut::Nut(int inner_n, float inner_d, int outer_n, float outer_d, float height)
{
	std::vector<vertice> in_circle = make_circle(inner_n, inner_d, height);
	std::vector<vertice> out_circle = make_circle(outer_n, outer_d, height);
	connect_circles(in_circle, out_circle);
	make_walls(in_circle);
	make_walls(out_circle);
}

void Nut::connect_one(std::vector<vertice> in, std::vector<vertice> out)
{
	vertice v1, v2, v3, tmp;
	double min_distance;
	for (unsigned i = 0; i < in.size(); i++)
	{
		v1 = in[i];
		v2 = in[(i + 1) % in.size()];
		v3 = out[0];
		min_distance = distance(v1, v2, v3);
		for (unsigned j = 1; j < out.size(); j++)
		{
			tmp = out[j];
			double tmp_dist = distance(v1, v2, tmp);
			if (tmp_dist < min_distance)
			{
				min_distance = tmp_dist;
				v3 = tmp;
			}
		}
		make_triangle_mirror_y(v1, v2, v3);
	}
}

void Nut::connect_circles(std::vector<vertice> in, std::vector<vertice> out)
{
	connect_one(in, out);
	connect_one(out, in);
}
