#ifndef _PRIMITIVE_H__
#define _PRIMITIVE_H__
#include "Vector3D.h"
#include "Ray.h"
#include "Surface.h"

class noIntersectionException : public std::exception
{ };

class Primitive
{
private:
public:
	Surface surface;
	Primitive()
	: Primitive(Surface())
	{}
	Primitive(const Surface& surf)
	: surface(surf)
	{}
	virtual Vector3DBase getIntersectionPoint(const Ray& ray) const = 0;
	virtual Vector3DBase getNormalVect(const Vector3DBase& point) const = 0;
	virtual void print() const = 0;
};

#endif