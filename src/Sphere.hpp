#pragma once
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
	Sphere(const std::shared_ptr<Surface>& surface)
	: Sphere(Vector3DBase(0,0,0), 1, surface)
	{}

	Sphere(Vector3DBase center, Vector3DBase::basetype radius, const std::shared_ptr<Surface>& surface)
	: Primitive(surface), center(center), radius(radius)
	{}

	std::unique_ptr<Vector3DBase> getIntersectionPoint(const Ray& ray) const override;
	Vector3DBase getNormalVect(const Vector3DBase& point) const override;
};
