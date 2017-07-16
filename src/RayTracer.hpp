#pragma once

#include <iostream>
#include <iomanip> 
#include <cstdint>
#include <fstream>
#include <memory>
#include <vector>
#include <omp.h>
#include <chrono>

#include "Vector3D.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "ArrayScene.hpp" 
#include "Light.hpp"
#include "Surface.hpp"
#include "Camera.hpp"

using Clock = std::chrono::high_resolution_clock;

class RayTracer
{
	using Bitmap = std::vector<Vector3DBase>;
private:

	Vector3DBase getPixelColor(const Ray& ray) const;
	Vector3DBase totalAmbient;
public:
	RayTracer(const std::shared_ptr<Scene>& scene);
	RayTracer(const std::shared_ptr<Scene>& scene, const Camera& camera);

	Bitmap getBitmap(int width, int height) const;

	std::shared_ptr<Scene> scene;
	Camera camera;


};