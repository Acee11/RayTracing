#pragma once
#include "Vector3D.hpp"

class Surface
{
public:
	Vector3DBase specular;
	Vector3DBase diffuse;
	Vector3DBase ambient;
	Vector3DBase::basetype shininess;

	Vector3DBase::basetype reflectance = 0.;
	Vector3DBase::basetype transparency = 0.;
	Vector3DBase::basetype refractionIdx = 1.;

};
