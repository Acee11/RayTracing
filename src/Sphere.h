#ifndef _SPHERE_H__
#define _SPHERE_H__
#include "Primitive.h"
#include "Ray.h"
#include "Vector3D.h"


class Sphere : public Primitive
{
private:
	Vector3D center;
	float radius;
public:
	Sphere(Vector3D center, float radius)
	: center(center), radius(radius)
	{ }

	Vector3D getIntersectionPoint(const Ray& ray) const;
};

#endif