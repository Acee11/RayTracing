#ifndef _SCENE_H__
#define _SCENE_H__
#include "Primitive.h"
#include "Ray.h"
#include "Vector3D.h"
#include "Light.h"


class Scene
{
private:
public:
	std::vector<Light> lights;
	void addLight(const Light& l)
	{
		lights.push_back(l);
	}
	virtual void addObject(Primitive const* object) = 0;
	virtual std::pair<const Primitive&, Vector3DBase> getIntersectingObject(const Ray& ray) const = 0;
};

#endif