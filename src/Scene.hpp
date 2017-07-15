#pragma once
#include <memory>

#include "Primitive.hpp"
#include "Ray.hpp"
#include "Vector3D.hpp"
#include "Light.hpp"


class Scene
{
public:
	std::vector<Light> lights;
	void addLight(const Light& l)
	{
		lights.push_back(l);
	}
	virtual void addObject(std::unique_ptr<const Primitive> object) = 0;
	virtual std::pair<Primitive const*, Vector3DBase> getIntersectingObject(const Ray& ray) const = 0;
};
