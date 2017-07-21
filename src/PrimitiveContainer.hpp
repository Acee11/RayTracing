#pragma once

#include "Vector3D.hpp"
#include "Primitive.hpp"

class PrimitiveContainer
{
public:
	virtual void addObject(std::unique_ptr<const Primitive> object) = 0;
	virtual std::tuple<Primitive const*, Vector3DBase> getIntersectingObject(const Ray& ray) const = 0;
};