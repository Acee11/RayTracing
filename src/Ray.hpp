#pragma once
#include "Vector3D.hpp"

class Ray
{
public:
	Vector3DBase operator () (float t) const;

	Vector3DBase eye;
	Vector3DBase offset;
};
