#ifndef _SPHERE_H__
#define _SPHERE_H__
#include "Primitive.h"
#include "Ray.h"
#include "Vector3D.h"


class Sphere : public Primitive
{
private:
	Vector3DBase center;
	Vector3DBase::basetype radius;
public:
	Sphere()
	: Sphere(Vector3DBase(0,0,0), 1)
	{}

	Sphere(Vector3DBase center, Vector3DBase::basetype radius)
	: Primitive(), center(center), radius(radius)
	{}

	Vector3DBase getIntersectionPoint(const Ray& ray) const;
	void print() const;

	friend std::ostream& operator << (std::ostream& stream, const Sphere& sphere);
};

#endif