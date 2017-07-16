#pragma once

#include <memory>

#include "Vector3D.hpp"
#include "Ray.hpp"
#include "Surface.hpp"

class noIntersectionException : public std::exception
{ };



class Primitive
{
private:
	virtual void print(std::ostream& stream) const = 0;
public:
	std::shared_ptr<Surface> surface;
	Primitive(const std::shared_ptr<Surface>& surface)
		: surface(surface)
	{}
	virtual std::unique_ptr<Vector3DBase> getIntersectionPoint(const Ray& ray) const = 0;
	virtual Vector3DBase getNormalVect(const Vector3DBase& point) const = 0;
	friend std::ostream& operator << (std::ostream& stream, const Primitive& primitive)
	{
		primitive.print(stream);
		return stream;
	}
};
