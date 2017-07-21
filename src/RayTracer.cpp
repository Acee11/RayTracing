#include "RayTracer.hpp"

RayTracer::RayTracer(const std::shared_ptr<Scene>& scene)
	: RayTracer(scene, Camera::getDefaultCamera())
{}

RayTracer::RayTracer(const std::shared_ptr<Scene>& scene,const Camera& camera)
	: scene(scene), camera(camera)
{
	totalAmbient = 0;
	for(const auto& light : scene->getLights())
    	totalAmbient += light.ambient;
}

Vector3DBase RayTracer::getPixelColor(const Ray& ray, int recursionLevel) const
{
	Vector3DBase dirTowardsPixel = ray.offset;
	const Primitive* intObj;
	Vector3DBase intPoint;
	std::tie(intObj, intPoint) = scene->getIntersectingObject(ray);
	Vector3DBase bgd_pixel(0.35);
	if(intObj == nullptr)
	{
		return bgd_pixel;
	}

	Vector3DBase finalColor = intObj->surface->ambient * totalAmbient;
	Vector3DBase normalVect = intObj->getNormalVect(intPoint);
	Vector3DBase dirTowardsCamera = -dirTowardsPixel;
	Vector3DBase::basetype pixDotNorm = dirTowardsPixel.dot(normalVect);
	Vector3DBase dirReflected = dirTowardsPixel - 2. * normalVect * pixDotNorm;
	Vector3DBase::basetype powVect = pow(dirReflected.dot(dirTowardsCamera), intObj->surface->shininess);

	Vector3DBase reflectedColor = 0.;
	Vector3DBase refractedColor = 0.;
	if(recursionLevel > 0)
	{
		Ray reflectedRay{intPoint + 0.1*dirReflected, dirReflected};
		reflectedColor = getPixelColor(reflectedRay, recursionLevel-1);

		// auto& n2 = intObj->surface->refractionIdx;

		// auto sinTheta2 = sqrt(1 - pixDotNorm*pixDotNorm)/n2;
		// Vector3DBase dirRefracted = (1./n2) * dirTowardsPixel +
		// 	(n2 - sqrt(1 - sinTheta2*sinTheta2)) * normalVect;
		// dirRefracted.normalize();
		auto& dirRefracted = dirTowardsPixel;
		Ray refractedRay{intPoint + 0.1*dirRefracted, dirRefracted};

		refractedColor = getPixelColor(refractedRay, recursionLevel-1);
	}


	for(const auto& light : scene->getLights())
	{
		Vector3DBase dirTowardsLight = (light.location - intPoint).normalize();
		Ray rayTowLight{intPoint + 0.1*dirTowardsLight, dirTowardsLight};
		const Primitive* shadowObj;
		Vector3DBase shadowIntPoint;
		Vector3DBase::basetype distFromLight = Vector3DBase::distance(intPoint, light.location);
		Vector3DBase::basetype lightPower = 1.;
		while(true)
		{
			if(lightPower < 0.001)
			{
				lightPower = 0.;
				break;
			}
			std::tie(shadowObj, shadowIntPoint) = scene->getIntersectingObject(rayTowLight);

			if(shadowObj == nullptr)
				break;
			if(Vector3DBase::distance(intPoint, shadowIntPoint) > distFromLight)
				break;

			lightPower *= shadowObj->surface->transparency;
			rayTowLight.eye = shadowIntPoint + 0.1*dirTowardsLight;
		}
		finalColor += ((intObj->surface->diffuse * dirTowardsLight.dot(normalVect) * light.diffuse) +
					(intObj->surface->specular * powVect * light.specular)) * lightPower;
	}
	return (1.- intObj->surface->transparency)*finalColor + intObj->surface->reflectance * reflectedColor + intObj->surface->transparency * refractedColor;
}

std::vector<Vector3DBase> RayTracer::getBitmap(int width, int height) const
{
	Bitmap bitmap(width*height);

	Camera::View view = camera.getView(width, height);

	// auto  start  = Clock::now();
	auto location = camera.location;
	auto frustumLocation = view.frustumTopLeft;
	auto deltaX = view.deltaX;
	auto deltaY = view.deltaY;
	int i, j;
	#pragma omp parallel for schedule(static) shared(bitmap, location, deltaY, deltaX, width, height) private(i, j)
	for(i = 0; i < height; ++i)
	{
		for(j = 0; j < width; ++j)
		{
			bitmap[i*width + j] = getPixelColor(
				Ray{location, ((frustumLocation + i*deltaY + j*deltaX) - location).normalize()},
				 2
			);
		}
	}

	// auto stop = Clock::now();
	// std::cout << "Time: "
 //            << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
 //            << "[ms]" << std::endl;

	return bitmap;
}