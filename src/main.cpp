#include <iostream>
#include <iomanip> 

#include "Vector3D.h"
#include "Sphere.h"
#include "Ray.h"
#include "ArrayScene.h" 
#include "Light.h"



int main()
{
	Vector3DBase bgd_pixel(0.75294117);
	constexpr int w = 300;
	constexpr int h = 300;
	constexpr int offset = 150;
	Vector3DBase camera(0, 0, -600);
	Vector3DBase view[w][h];
	ArrayScene scene;
	scene.addObject(new Sphere({-50, 0, -100}, 70));
	scene.addLight({{100, 100, -70}, 0.7});

	for(int i = offset-1; i >= -offset; --i)
	{
		int i_offset = i + offset;
		for(int j = -offset; j < offset; ++j)
		{
			int j_offset = j + offset;
			Vector3DBase pixel(j, i, 0);
			Ray ray(camera, (pixel-camera).normalized());
			try
			{
				auto ret = scene.getIntersectingObject(ray);
				for(const auto& l : scene.lights)
				{
					Ray rayToLight(ret.second, (l.position - ret.second).normalized());	
					try
					{
						auto ret1 = scene.getIntersectingObject(rayToLight);
						view[j_offset][i_offset] = l.brightness * ret1.first.surface.color;
					}
					catch(const noIntersectionException& e)
					{
						view[j_offset][i_offset] = 0;
					}
						
				}
			}
			catch(const noIntersectionException& e)
			{
				view[j_offset][i_offset] = bgd_pixel;
			}
		}
	}
}