#pragma once

#include <iostream>
#include <iomanip> 
#include <cstdint>
#include <fstream>
#include <memory>
#include <vector>
#include <thread>

#include "Vector3D.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "ArrayScene.hpp" 
#include "Light.hpp"
#include "Surface.hpp"
#include "Camera.hpp"

class RayTracer
{
	using Bitmap = std::vector<Vector3DBase>;
private:
	void fillBitmap(Bitmap& bitmap, const Camera::View& view, int beg_i, int beg_j, int end_i, int end_j) const;

	Vector3DBase getPixelColor(const Ray& ray) const;
	Vector3DBase totalAmbient;
public:
	RayTracer(const std::shared_ptr<Scene>& scene);
	RayTracer(const std::shared_ptr<Scene>& scene, const Camera& camera);

	Bitmap getBitmap(int width, int height) const;

	std::shared_ptr<Scene> scene;
	Camera camera;


};