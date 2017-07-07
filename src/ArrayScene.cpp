#include "ArrayScene.h"

void ArrayScene::addObject(Primitive const* object)
{
	objects.push_back(std::unique_ptr<const Primitive>(object));
}

std::pair<const Primitive&, Vector3DBase> ArrayScene::getIntersectingObject(const Ray& ray) const
{
	Primitive const* closestObject = nullptr;
	Vector3DBase closestIntPoint(0,0,0);
	float minDist = INF;
	for(const auto& object : objects)
	{
		try
		{
			Vector3DBase intPoint = object.get()->getIntersectionPoint(ray);
			float intDist  = Vector3DBase::distance(intPoint, ray.eye);
			if(intDist < 0.1)
				continue;
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
	if(closestObject == nullptr)
		throw noIntersectionException();
	return std::pair<const Primitive&, Vector3DBase>(*closestObject, closestIntPoint);
}