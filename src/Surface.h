#ifndef _SURFACE_H__
#define _SURFACE_H__
#include "Vector3D.h"

class Surface
{
public:
	Vector3DBase color;

	Surface()
	: Surface({0.5, 0.5, 0.5})
	{}
	Surface(Vector3DBase c)
	: color(c)
	{}
};

#endif