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
		try
		{
			Vector3DBase intPoint = object.get()->getIntersectionPoint(ray);
			float intDist  = Vector3DBase::distance(intPoint, ray.eye);
			if(intDist < minDist)
			{
				closestObject = object.get();
				closestIntPoint = intPoint;
				minDist = intDist;
			}
		}
		catch(const noIntersectionException& e)
		{
			continue;
		}
	}
	return std::make_pair(closestObject, closestIntPoint);
}