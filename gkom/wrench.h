#pragma once

#include "object.h"

class Wrench : public Object
{
public:
	Wrench() {};
	Wrench(double d, double w, double h);

private:
	void make_handle(double d, double w, double h);
	void make_head(double d, double w, double h);
};