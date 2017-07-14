#include <iostream>
#include <iomanip> 
#include <cstdint>
#include <fstream>
#include <cmath>

#include "Vector3D.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "ArrayScene.hpp" 
#include "Light.hpp"
#include "Surface.hpp"



int main()
{
	Vector3DBase bgd_pixel(0.7);
	constexpr int w = 1920;
	constexpr int h = 1080;
	constexpr int wOffset = w/2;
	constexpr int hOffset = h/2;
	Vector3DBase camera(0, 0, -2400);
	auto view = std::make_unique<Vector3DBase[]>(w*h);
	ArrayScene scene;
	Surface sphereSurface{
		{0.5, 0.3, 0.6},
		{0.1, 0.3, 0.6},
		{0.2, 0.1, 0.5},
		80.
	};
	scene.addObject(std::make_unique<Sphere>(
		Vector3DBase(800, 0, 400),
		 200,
		 sphereSurface
	));
	scene.addObject(std::make_unique<Sphere>(
		Vector3DBase(300, 0, 400),
		 135,
		 sphereSurface
	));
	scene.addObject(std::make_unique<Sphere>(
		Vector3DBase(-300, 0, 400),
		 135,
		 sphereSurface
	));
	scene.addObject(std::make_unique<Sphere>(
		Vector3DBase(-800, 0, 400),
		 200,
		 sphereSurface
	));

	scene.addLight(Light{
		{0, 0, 0},
		{ 0.1, 0.3, 0.1 },
        { 0.6, 0.6, 0.8 },
        { 0.1, 0.1, 0.1 }
    });

	Vector3DBase ambient_lighting = 0;
    for(const auto& light : scene.lights)
    	ambient_lighting += light.ambient;
    //ambient_lighting /= (Vector3DBase::basetype)scene.lights.size();
	for(int i = hOffset; i > -hOffset; --i)
	{
		int i_offset = hOffset - i;
		for(int j = -wOffset; j < wOffset; ++j)
		{
			int j_offset = j + wOffset;

			Vector3DBase pixel(j, i, 0);
			Vector3DBase dirTowardsPixel = (pixel-camera).normalize();
			Ray ray{camera, dirTowardsPixel};

			auto ret = scene.getIntersectingObject(ray);
			auto intObj = ret.first;
			auto intPoint = ret.second;
			if(intObj == nullptr)
			{
				view[i_offset*w + j_offset] = bgd_pixel;
				continue;
			}

			Vector3DBase finalColor = intObj->surface.ambient * ambient_lighting;

			for(const auto& light : scene.lights)
			{
				Vector3DBase dirTowardsLight = (light.position - intPoint).normalize();
				Ray rayToLight{intPoint + 0.01*dirTowardsLight, dirTowardsLight};	

				//auto ret1 = scene.getIntersectingObject(rayToLight);
				//if(ret1.first != nullptr)
				//	continue;

				Vector3DBase normalVect = intObj->getNormalVect(intPoint);
				finalColor += intObj->surface.diffuse * 
					dirTowardsLight.dot(normalVect) * 
					light.diffuse;


				Vector3DBase dirTowardsCamera = -dirTowardsPixel;
				Vector3DBase dirReflected = dirTowardsPixel - 2. * normalVect * (dirTowardsPixel.dot(normalVect));

				finalColor += intObj->surface.specular *
					pow(dirReflected.dot(dirTowardsCamera), intObj->surface.shininess) *
					light.specular;

			}
			view[i_offset*w + j_offset] = finalColor;
		}
	}

	

	//Vector3D<uint8_t>* view_int = new Vector3D<uint8_t>[w*h];
	auto view_int = std::make_unique< Vector3D<uint8_t>[] >(w*h);
	for(int i = 0; i < h; ++i)
	{
		for(int j = 0; j < w; ++j)
		{
			view[i*w + j].x = std::min((float)1., std::max((float)0., view[i*w + j].x));
			view[i*w + j].y = std::min((float)1., std::max((float)0., view[i*w + j].y));
			view[i*w + j].z = std::min((float)1., std::max((float)0., view[i*w + j].z));
			view_int[i*w + j] = {(uint8_t)(view[i*w + j].x*255.), (uint8_t)(view[i*w + j].y*255.), (uint8_t)(view[i*w + j].z*255.)};
		}
	}

	std::ofstream myfile;
	myfile.open ("img/file.data", std::ios::binary);
	myfile.write((const char*)view_int.get(), w*h*sizeof(Vector3D<uint8_t>));
	myfile.close();

	return 0;
}