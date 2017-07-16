#include <iostream>
#include <iomanip> 
#include <cstdint>
#include <fstream>
#include <cmath>
#include <memory>

#include "Vector3D.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "RayTracer.hpp"
#include "ArrayScene.hpp" 
#include "Light.hpp"
#include "Surface.hpp"
#include "Camera.hpp"



int main()
{
	constexpr int w = 1920;
	constexpr int h = 1080;

	Camera camera{{0, 0, -1400}, {0,0,0}, 70};
	auto scene = std::make_shared<ArrayScene>();

	auto sphereSurface = std::make_shared<Surface>(Surface{
		{0.5, 0.3, 0.6},
		{0.1, 0.3, 0.6},
		{0.2, 0.1, 0.5},
		80.
	});

	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(800, 0, 400),
		 200,
		 sphereSurface
	));
	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(300, 0, 400),
		 135,
		 sphereSurface
	));
	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(-300, 0, 400),
		 135,
		 sphereSurface
	));
	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(-800, 0, 400),
		 200,
		 sphereSurface
	));

	scene->addLight(Light{
		{0, 0, 0},
		{ 0.1, 0.3, 0.1 },
        { 0.6, 0.6, 0.8 },
        { 0.1, 0.1, 0.1 }
    });

    RayTracer rayTracer(scene, camera);

	auto bitmap = rayTracer.getBitmap(w, h);

	std::vector< Vector3D<uint8_t> > bitmapInt(w*h);
	for(int i = 0; i < h; ++i)
	{
		for(int j = 0; j < w; ++j)
		{
			bitmap[i*w + j].x = std::min((float)1., std::max((float)0., bitmap[i*w + j].x));
			bitmap[i*w + j].y = std::min((float)1., std::max((float)0., bitmap[i*w + j].y));
			bitmap[i*w + j].z = std::min((float)1., std::max((float)0., bitmap[i*w + j].z));
			bitmapInt[i*w + j] = {(uint8_t)(bitmap[i*w + j].x*255.), (uint8_t)(bitmap[i*w + j].y*255.), (uint8_t)(bitmap[i*w + j].z*255.)};
		}
	}

	std::ofstream myfile;
	myfile.open ("img/file.data", std::ios::binary);
	myfile.write(reinterpret_cast<const char*>(&bitmapInt[0]), bitmapInt.size()*sizeof(Vector3D<uint8_t>));
	myfile.close();
	return 0;
}