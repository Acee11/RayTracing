#include "RayTracer.hpp"

RayTracer::RayTracer(const std::shared_ptr<Scene>& scene)
	: RayTracer(scene, Camera::getDefaultCamera())
{}

RayTracer::RayTracer(const std::shared_ptr<Scene>& scene,const Camera& camera)
	: scene(scene), camera(camera)
{
	totalAmbient = 0;
	for(const auto& light : scene->lights)
    	totalAmbient += light.ambient;
}

Vector3DBase RayTracer::getPixelColor(const Ray& ray) const
{
	Vector3DBase dirTowardsPixel = ray.offset;
	auto ret = scene->getIntersectingObject(ray);
	auto intObj = ret.first;
	auto intPoint = ret.second;
	Vector3DBase bgd_pixel(0.7);
	if(intObj == nullptr)
	{
		return bgd_pixel;
	}

	Vector3DBase finalColor = intObj->surface->ambient * totalAmbient;

	for(const auto& light : scene->lights)
	{
		Vector3DBase dirTowardsLight = (light.position - intPoint).normalize();

		Vector3DBase normalVect = intObj->getNormalVect(intPoint);
		finalColor += intObj->surface->diffuse * 
			dirTowardsLight.dot(normalVect) * 
			light.diffuse;


		Vector3DBase dirTowardsCamera = -dirTowardsPixel;
		Vector3DBase dirReflected = dirTowardsPixel - 2. * normalVect * (dirTowardsPixel.dot(normalVect));

		finalColor += intObj->surface->specular *
			pow(dirReflected.dot(dirTowardsCamera), intObj->surface->shininess) *
			light.specular;

	}
	return finalColor;
}

std::vector<Vector3DBase> RayTracer::getBitmap(int width, int height) const
{
	Bitmap bitmap(width*height);

	Camera::View view = camera.getView(width, height);

	auto  start  = Clock::now();
	auto location = camera.location;
	auto frustumLocation = view.frustumTopLeft;
	auto deltaX = view.deltaX;
	auto deltaY = view.deltaY;
	int i, j;
	#pragma omp parallel for schedule(static) num_threads(4) shared(bitmap, location, deltaY, deltaX, width, height) private(i, j)
	for(i = 0; i < height; ++i)
	{
		for(j = 0; j < width; ++j)
		{
			bitmap[i*width + j] = getPixelColor(Ray{location, ((frustumLocation + i*deltaY + j*deltaX) - location).normalize()});
		}
	}

	auto stop = Clock::now();
	std::cout << "Time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
            << "[ms]" << std::endl;

	return bitmap;
}