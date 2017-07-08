#include "ArrayScene.h"

void ArrayScene::addObject(Primitive const* object)
{
	objects.push_back(std::unique_ptr<const Primitive>(object));
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
	return std::pair<Primitive const*, Vector3DBase>(closestObject, closestIntPoint);
}