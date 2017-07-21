#pragma once
#include <memory>
#include <vector>

#include "Primitive.hpp"
#include "PrimitiveContainer.hpp"
#include "Ray.hpp"
#include "Vector3D.hpp"
#include "Light.hpp"


class Scene
{
private:
	std::unique_ptr<PrimitiveContainer> container;
public:
	std::vector<Light> lights;
	Scene();
	Scene(std::unique_ptr<PrimitiveContainer> container);
	const std::vector<Light>& getLights() const;
	void addLight(const Light& l);
	void addObject(const std::unique_ptr<const Primitive> object);
	std::tuple<Primitive const*, Vector3DBase> getIntersectingObject(const Ray& ray) const;
};
