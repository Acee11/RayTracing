#ifndef _PRIMITIVE_H__
#define _PRIMITIVE_H__
#include "Vector3D.h"
#include "Ray.h"

class noIntersectionException : public std::exception
{ };

class Primitive
{
public:
	virtual Vector3D getIntersectionPoint(const Ray& ray) const = 0;
};

#endif