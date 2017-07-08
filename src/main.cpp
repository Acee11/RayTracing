#include <iostream>
#include <iomanip> 
#include <cstdint>
#include <fstream>
#include <cmath>

#include "Vector3D.h"
#include "Sphere.h"
#include "Ray.h"
#include "ArrayScene.h" 
#include "Light.h"
#include "Surface.h"



int main()
{
	Vector3DBase bgd_pixel(0.7);
	constexpr int w = 3200;
	constexpr int h = 2400;
	constexpr int wOffset = w/2;
	constexpr int hOffset = h/2;
	Vector3DBase camera(0, 0, -2400);
	Vector3DBase* view = new Vector3DBase[w*h];
	ArrayScene scene;
	Surface sphereSurface{
		{0.5, 0.3, 0.6},
		{0.1, 0.3, 0.6},
		{0.2, 0.1, 0.5},
		80.
	};
	scene.addObject(new Sphere(
		{1200, 0, 200},
		 250,
		 sphereSurface
	));
	scene.addObject(new Sphere(
		{400, 0, 200},
		 235,
		 sphereSurface
	));
	scene.addObject(new Sphere(
		{-400, 0, 200},
		 235,
		 sphereSurface
	));
	scene.addObject(new Sphere(
		{-1200, 0, 200},
		 250,
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
			Ray ray(camera, dirTowardsPixel);

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
				Ray rayToLight(intPoint + 0.01*dirTowardsLight, dirTowardsLight);	

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
			/*
			*/
		}
	}

	

	Vector3D<uint8_t>* view_short = new Vector3D<uint8_t>[w*h];
	for(int i = 0; i < h; ++i)
	{
		for(int j = 0; j < w; ++j)
		{
			view[i*w + j].x = std::min((float)1., std::max((float)0., view[i*w + j].x));
			view[i*w + j].y = std::min((float)1., std::max((float)0., view[i*w + j].y));
			view[i*w + j].z = std::min((float)1., std::max((float)0., view[i*w + j].z));
			view_short[i*w + j] = {(uint8_t)(view[i*w + j].x*255.), (uint8_t)(view[i*w + j].y*255.), (uint8_t)(view[i*w + j].z*255.)};
		}
	}

	std::ofstream myfile;
	myfile.open ("file.data", std::ios::binary);
	myfile.write((const char*)view_short, w*h*sizeof(Vector3D<uint8_t>));
	myfile.close();
	delete view;
	delete view_short;

	return 0;
}