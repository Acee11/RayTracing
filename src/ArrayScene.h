#ifndef _ARRAY_SCENE_H__
#define _ARRAY_SCENE_H__

#define INF 10000000.0 // TODO(change this)

#include <vector>
#include <memory>
#include "Scene.h"
#include "Primitive.h"
#include "Ray.h"
#include "Vector3D.h"


class ArrayScene : public Scene
{
private:
	std::vector< std::unique_ptr<const Primitive> > objects;
public:
	void addObject(Primitive const* object);
	std::pair<Primitive const*, Vector3DBase> getIntersectingObject(const Ray& ray) const;
};

#endif