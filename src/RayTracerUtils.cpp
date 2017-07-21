#include "RayTracerUtils.hpp"

template<class T>
void RayTracerUtils::constrain(T& elem, const T& low, const T& high)
{
	elem = std::min(high, std::max(low, elem));
}

void RayTracerUtils::normalizeBitmap(std::vector<Vector3DBase>& bitmap)
{
	std::for_each(
		bitmap.begin(),
		bitmap.end(),
		[](Vector3DBase& v) 
		{
			constrain(v.x, static_cast<Vector3DBase::basetype>(0.), static_cast<Vector3DBase::basetype>(1.));
			constrain(v.y, static_cast<Vector3DBase::basetype>(0.), static_cast<Vector3DBase::basetype>(1.));
			constrain(v.z, static_cast<Vector3DBase::basetype>(0.), static_cast<Vector3DBase::basetype>(1.));
		}
	);
}
std::vector< Vector3D<uint8_t> > RayTracerUtils::floatToIntBitmap(const std::vector<Vector3DBase>& floatBitmap)
{
	std::vector< Vector3D<uint8_t> > intBitmap(floatBitmap.size());
	std::transform(
		floatBitmap.begin(),
		floatBitmap.end(),
		intBitmap.begin(),
		[](const Vector3DBase& v)
		{
			return Vector3D<uint8_t>(
				static_cast<uint8_t>(v.x*255.),
				static_cast<uint8_t>(v.y*255.),
				static_cast<uint8_t>(v.z*255.)
			);
		}
	);

	return intBitmap;
}
void RayTracerUtils::saveBitmapToFile(const std::vector< Vector3D<uint8_t> >& bitmap, const std::string& fileName)
{
	std::ofstream imgfile;
	imgfile.open (fileName + ".rgb", std::ios::binary);
	if(!imgfile.is_open())
		throw std::runtime_error("Cannot open a file");
	imgfile.write(reinterpret_cast<const char*>(&bitmap[0]), bitmap.size()*sizeof(Vector3D<uint8_t>));
}

void RayTracerUtils::convertBitmapToJpg(const std::string& fileName, int w, int h)
{
	system(("convert -size \"" + std::to_string(w) + "x" + std::to_string(h) + "\" -depth 8 " + fileName + ".rgb " + fileName + ".jpg").c_str());
	system(("rm " + fileName + ".rgb").c_str());
}