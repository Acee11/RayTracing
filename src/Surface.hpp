#pragma once
#include "Vector3D.hpp"

class Surface
{
public:
	Vector3DBase specular;
	Vector3DBase diffuse;
	Vector3DBase ambient;
	Vector3DBase::basetype shininess;
};
