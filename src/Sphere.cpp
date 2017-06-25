#include "Sphere.h"

Vector3D Sphere::getIntersectionPoint(const Ray& ray) const
{
	constexpr float epsilon = 0.01;
	float a = ray.offset.normSquared();
	float b = 2 * ray.offset.dot(ray.eye - center);
	float c = (ray.eye - center).normSquared() - radius*radius;
	float delta = b*b - 4.0*a*c;
	if(delta < -epsilon) // no intersection points
	{
		throw noIntersectionException();
	}
	else if(delta < epsilon)
	{
		float t0 = -b/(2.0*a);
		return ray(t0);
	}
	else
	{
		float t0 = (-b + sqrt(delta)) / (2*a);
		float t1 = (-b - sqrt(delta)) / (2*a);

		Vector3D point1 = ray(t0);
		Vector3D point2 = ray(t1);

		if(point1.z < point2.z)
			return point1;
		else
			return point2;
	}
}