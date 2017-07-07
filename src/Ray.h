#ifndef _RAY_H__
#define _RAY_H__
#include "Vector3D.h"

class Ray
{
public:
	Ray(Vector3DBase eye, Vector3DBase offset)
	: eye(eye), offset(offset)
	{ }

	Vector3DBase operator () (float t) const;

	Vector3DBase eye;
	Vector3DBase offset;
};

#endif