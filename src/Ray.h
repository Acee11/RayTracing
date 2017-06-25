#ifndef _RAY_H__
#define _RAY_H__
#include "Vector3D.h"

class Ray
{
public:
	Ray(Vector3D eye, Vector3D offset)
	: eye(eye), offset(offset)
	{ }

	Vector3D operator () (float t) const;

	Vector3D eye;
	Vector3D offset;
};

#endif