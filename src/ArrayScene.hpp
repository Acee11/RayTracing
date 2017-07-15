#pragma once

#include <vector>
#include <memory>
#include <limits>

#include "Scene.hpp"
#include "Primitive.hpp"
#include "Ray.hpp"
#include "Vector3D.hpp"

#define INF (std::numeric_limits<Vector3DBase::basetype>::max())

class ArrayScene : public Scene
{
private:
	std::vector< std::unique_ptr<const Primitive> > objects;
public:
	void addObject(std::unique_ptr<const Primitive> object) override;
	std::pair<Primitive const*, Vector3DBase> getIntersectingObject(const Ray& ray) const override;
};
