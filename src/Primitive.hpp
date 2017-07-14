#ifndef _PRIMITIVE_H__
#define _PRIMITIVE_H__
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
	Surface surface;
	Primitive()
	: Primitive(Surface())
	{}
	Primitive(const Surface& surf)
	: surface(surf)
	{}
	virtual Vector3DBase getIntersectionPoint(const Ray& ray) const = 0;
	virtual Vector3DBase getNormalVect(const Vector3DBase& point) const = 0;
	friend std::ostream& operator << (std::ostream& stream, const Primitive& primitive)
	{
		primitive.print(stream);
		return stream;
	}
};

#endif