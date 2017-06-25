#include "ArrayScene.h"

void ArrayScene::addObject(std::unique_ptr<Primitive> object)
{
	objects.push_back(std::move(object));
}
const Primitive& ArrayScene::getIntersectingObject(const Ray& ray) const
{
	Vector3D closestIntPoint;
	for(const auto& object : objects)
	{
		try
		{
			Vector3D intPoint = object.get()->getIntersectionPoint(ray);
			if(intPoint.z < closestIntPoint.z)
			{
				//closestObject = object;
				closestIntPoint = intPoint;
			}
		}
		catch(const noIntersectionException& e)
		{
			continue;
		}
	}
/*
	if(closestObject == nullptr)
		throw noIntersectionException();
	return *closestObject;
*/
	return;
}