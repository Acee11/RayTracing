#ifndef _SPHERE_H__
#define _SPHERE_H__
#include "Primitive.hpp"
#include "Ray.hpp"
#include "Vector3D.hpp"


class Sphere : public Primitive
{
private:
	void print(std::ostream& stream) const override;
	
	Vector3DBase center;
	Vector3DBase::basetype radius;
public:
	Sphere()
	: Sphere(Vector3DBase(0,0,0), 1)
	{}

	Sphere(Vector3DBase center, Vector3DBase::basetype radius)
	: Primitive(), center(center), radius(radius)
	{}

	Sphere(Vector3DBase center, Vector3DBase::basetype radius, Surface surf)
	: Primitive(surf), center(center), radius(radius)
	{}

	Vector3DBase getIntersectionPoint(const Ray& ray) const override;
	Vector3DBase getNormalVect(const Vector3DBase& point) const override;
};

#endif