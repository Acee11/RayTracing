#ifndef _SURFACE_H__
#define _SURFACE_H__
#include "Vector3D.h"

class Surface
{
public:
	Vector3DBase specular;
	Vector3DBase diffuse;
	Vector3DBase ambient;
	Vector3DBase::basetype shininess;
};

#endif