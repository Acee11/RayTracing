#include <iostream>
#include <iomanip> 
#include <cstdint>
#include <fstream>
#include <cmath>
#include <memory>
#include <string> 

#include "Vector3D.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "RayTracer.hpp"
#include "ArrayContainer.hpp" 
#include "Light.hpp"
#include "Surface.hpp"
#include "Camera.hpp"
#include "RayTracerUtils.hpp"


int main()
{
	//    1920 x 1080
	//4K  4096 × 2304
	//8K  8192 × 4608
	//16K 16384 x 9216 
	constexpr int w = 4096;
	constexpr int h = 2304;

	//Camera camera{{1900, 0, 200}, {0,-60,0}, 70};
	Camera camera{{0, 0, -1500}, {0,0,0}, 70};
	auto scene = std::make_shared<Scene>(std::make_unique<ArrayContainer>());

	auto mirrorSurface = std::make_shared<Surface>(Surface{
		{0., 0., 0.},
		{0., 0., 0.},
		{0., 0., 0.},
		8.,
		1.
	});

	auto glassSurface = std::make_shared<Surface>(Surface{
		{0., 0., 0.},
		{0., 0., 0.},
		{0., 0., 0.},
		8.,
		0.,
		1.,
		1.
	});

	auto sphereSurface = std::make_shared<Surface>(Surface{
		{0.5, 0.3, 0.6},
		{0.4, 0.3, 0.6},
		{0.2, 0.1, 0.3},
		8.,
		0.20,
		0.2
	});



	scene->addLight(Light{
		{-800, 0, 0},
		{0.2, 0.2, 0.2},
        {0.2, 0.4, 0.6},
        {0.3, 0.3, 0.3}
    });

    scene->addLight(Light{
		{800, 0, 0},
		{0.1, 0.1, 0.1},
        {0.2, 0.4, 0.6},
        {0.5, 0.5, 0.5}
    });


 //    scene->addObject(std::make_unique<Sphere>(
	// 	Vector3DBase(0, 0, 1000),
	// 	 1000,
	// 	 glassSurface
	// ));

	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(0, 0, 2000),
		 500,
		 mirrorSurface
	));
	// scene->addObject(std::make_unique<Sphere>(
	// 	Vector3DBase(-2000, 1000, 1000),
	// 	 1000,
	// 	 mirrorSurface
	// ));
	// scene->addObject(std::make_unique<Sphere>(
	// 	Vector3DBase(2000, -1000, 1000),
	// 	 1000,
	// 	 mirrorSurface
	// ));

	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(500, 0, 1000),
		 200,
		 sphereSurface
	));
	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(-500, 0, 1000),
		 200,
		 sphereSurface
	));
	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(0, 500, 1000),
		 200,
		 sphereSurface
	));
	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(0, -500, 1000),
		 200,
		 sphereSurface
	));

	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(-500, 300, 1000),
		 100,
		 sphereSurface
	));
	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(-500, -300, 1000),
		 100,
		 sphereSurface
	));
	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(-800, 0, 1000),
		 100,
		 sphereSurface
	));

	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(500, 300, 1000),
		 100,
		 sphereSurface
	));
	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(500, -300, 1000),
		 100,
		 sphereSurface
	));
	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(800, 0, 1000),
		 100,
		 sphereSurface
	));

	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(0, -800, 1000),
		 100,
		 sphereSurface
	));
	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(-300, -500, 1000),
		 100,
		 sphereSurface
	));
	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(300, -500, 1000),
		 100,
		 sphereSurface
	));

	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(0, 800, 1000),
		 100,
		 sphereSurface
	));
	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(-300, 500, 1000),
		 100,
		 sphereSurface
	));
	scene->addObject(std::make_unique<Sphere>(
		Vector3DBase(300, 500, 1000),
		 100,
		 sphereSurface
	));
	


    RayTracer rayTracer(scene, camera);

    auto bitmap = rayTracer.getBitmap(w, h);
	RayTracerUtils::normalizeBitmap(bitmap);
	auto intBitmap = RayTracerUtils::floatToIntBitmap(bitmap);
	std::string fName = "img/outImg";
	RayTracerUtils::saveBitmapToFile(intBitmap, fName);
	RayTracerUtils::convertBitmapToJpg(fName, w, h);

  //   for(int i = -2000, cnt = 0; i <= 2000; i += 25, ++cnt)
  //   {
  //   	scene->lights[0].location = {static_cast<Vector3DBase::basetype>(i), 0., 0.};
		// auto bitmap = rayTracer.getBitmap(w, h);
		// RayTracerUtils::normalizeBitmap(bitmap);
		// auto intBitmap = RayTracerUtils::floatToIntBitmap(bitmap);
		// std::string fName = "img/outImg" + std::to_string(cnt);
		// RayTracerUtils::saveBitmapToFile(intBitmap, fName);
		// RayTracerUtils::convertBitmapToJpg(fName);

		// constexpr int max = 4000/25;
		// std::cout << '\r' << (cnt*100)/max << '%' << std::flush;
  //   }

 //    Vector3DBase::basetype angle;
 //    int cnt = 0;
	// for(angle = -55.0; angle <= 55.0; angle += 0.5, ++cnt)
	// {
	// 	rayTracer.camera.angle.y = angle;
	// 	auto bitmap = rayTracer.getBitmap(w, h);
	// 	RayTracerUtils::normalizeBitmap(bitmap);
	// 	auto intBitmap = RayTracerUtils::floatToIntBitmap(bitmap);
	// 	std::string fName = "img/" + std::to_string(cnt);
	// 	RayTracerUtils::saveBitmapToFile(intBitmap, fName);
	// 	RayTracerUtils::convertBitmapToJpg(fName, w, h);

	// 	constexpr int max = 2*2*55;
	// 	std::cout << '\r' << (cnt*100)/max << '%' << std::flush;
	// }
 //    std::cout << std::endl;

	
	return 0;
}