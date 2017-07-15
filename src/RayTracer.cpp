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

void RayTracer::fillBitmap(
	Bitmap& bitmap, 
	const Camera::View& view,
	int beg_i, int beg_j, 
	int end_i, int end_j
) const
{
	auto YIterator = view.frustumTopLeft + static_cast<Vector3DBase::basetype>(beg_i) * view.deltaY
		+ static_cast<Vector3DBase::basetype>(beg_j) * view.deltaX;
	for(int i = beg_i; i < end_i; ++i, YIterator += view.deltaY)
	{
		auto XIterator = YIterator;
		for(int j = beg_j; j < end_j; ++j, XIterator += view.deltaX)
		{
			auto direction = (XIterator - camera.location).normalize();
			Ray rayTowPixel{camera.location, direction};
			if(i*view.width + j < 0)
				std::cout << 1;
			bitmap[i*view.width + j] = getPixelColor(rayTowPixel);
		}
	}
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

	int width2 = width/2;
	int height2 = height/2;

	std::thread t1(&RayTracer::fillBitmap, this, std::ref(bitmap), std::ref(view), 0, 0, height2, width2);
	std::thread t2(&RayTracer::fillBitmap, this, std::ref(bitmap), std::ref(view), 0, width2, height2, width);
	std::thread t3(&RayTracer::fillBitmap, this, std::ref(bitmap), std::ref(view), height2, 0, height, width2);
	std::thread t4(&RayTracer::fillBitmap, this, std::ref(bitmap), std::ref(view), height2, width2, height, width);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	return bitmap;
}