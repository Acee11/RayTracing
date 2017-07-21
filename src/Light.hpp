#pragma once
#include "Vector3D.hpp"

class Light
{
public:
	
	Vector3DBase location;
	Vector3DBase specular;
	Vector3DBase diffuse;
	Vector3DBase ambient;
};
