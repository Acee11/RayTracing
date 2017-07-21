#include "Scene.hpp"

Scene::Scene(std::unique_ptr<PrimitiveContainer> container)
	: container(std::move(container))
{}

const std::vector<Light>& Scene::getLights() const
{
	return lights;
}

void Scene::addLight(const Light& l)
{
	lights.push_back(l);
}

void Scene::addObject(std::unique_ptr<const Primitive> object)
{
	container->addObject(std::move(object));
}

std::tuple<Primitive const*, Vector3DBase> Scene::getIntersectingObject(const Ray& ray) const
{
	return container->getIntersectingObject(ray);
}