#ifndef _SCENE_H__
#define _SCENE_H__
#include "Primitive.h"
#include "Ray.h"

class Scene
{
private:
public:
	virtual void addObject(const Primitive& object) = 0;
	virtual const Primitive& getIntersectingObject(const Ray& ray) const = 0;
};

#endif