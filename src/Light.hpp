#ifndef _LIGHT_H__
#define _LIGHT_H__
#include "Vector3D.hpp"

class Light
{
public:
	
	Vector3DBase position;
	Vector3DBase specular;
	Vector3DBase diffuse;
	Vector3DBase ambient;
};

#endif