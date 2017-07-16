#include "ArrayScene.hpp"

void ArrayScene::addObject(std::unique_ptr<const Primitive> object)
{
	objects.push_back(std::move(object));
}

std::pair<Primitive const*, Vector3DBase> ArrayScene::getIntersectingObject(const Ray& ray) const
{
	Primitive const* closestObject = nullptr;
	Vector3DBase closestIntPoint;
	float minDist = INF;
	for(const auto& object : objects)
	{
		auto intPoint = object->getIntersectionPoint(ray);
		if(intPoint == nullptr)
			continue;
		float intDist  = Vector3DBase::distance(*intPoint, ray.eye);
		if(intDist < minDist)
		{
			closestObject = object.get();
			closestIntPoint = *intPoint;
			minDist = intDist;
		}
	}
	return std::make_pair(closestObject, closestIntPoint);
}