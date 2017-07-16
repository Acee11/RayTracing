#include "Sphere.hpp"

std::unique_ptr<Vector3DBase> Sphere::getIntersectionPoint(const Ray& ray) const
{
	constexpr Vector3DBase::basetype epsilon = 0.01;
	Vector3DBase::basetype a = ray.offset.normSquared();
	Vector3DBase::basetype b = 2 * ray.offset.dot(ray.eye - center);
	Vector3DBase::basetype c = (ray.eye - center).normSquared() - radius*radius;
	Vector3DBase::basetype delta = b*b - 4.0*a*c;
	if(delta < -epsilon) // no intersection points
	{
		return std::unique_ptr<Vector3DBase>(nullptr);
	}
	else if(delta < epsilon)
	{
		Vector3DBase::basetype t0 = -b/(2.0*a);
		if(t0 < 0)
			return std::unique_ptr<Vector3DBase>(nullptr);
		else
			return std::make_unique<Vector3DBase>(ray(t0));
	}
	else
	{

		Vector3DBase::basetype t0 = (-b + sqrt(delta)) / (2.*a);
		Vector3DBase::basetype t1 = (-b - sqrt(delta)) / (2.*a);

		if(t1 < t0)
			std::swap(t1, t0);
		if(t0 < 0 )
		{
			if(t1 < 0)
				return std::unique_ptr<Vector3DBase>(nullptr);;
			return std::make_unique<Vector3DBase>(ray(t1));
		}
		else
			return std::make_unique<Vector3DBase>(ray(t0));
	}
}

Vector3DBase Sphere::getNormalVect(const Vector3DBase& point) const
{
	return (point-center).normalize();
}

void Sphere::print(std::ostream& stream) const
{
	stream << center << ", " << radius;
}