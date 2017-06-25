#ifndef _ARRAY_SCENE_H__
#define _ARRAY_SCENE_H__

#include <vector>
#include <memory>
#include "Scene.h"
#include "Primitive.h"
#include "Ray.h"


class ArrayScene : public Scene
{
private:
	std::vector< std::unique_ptr<const Primitive> > objects;
public:
	void addObject(std::unique_ptr<const Primitive> object);
	const Primitive& getIntersectingObject(const Ray& ray) const;
};

#endif