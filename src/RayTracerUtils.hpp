#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <algorithm>

#include "Vector3D.hpp"

namespace RayTracerUtils
{
	template<class T>
	void constrain(T& elem, const T& low, const T& high); 
	void normalizeBitmap(std::vector<Vector3DBase>& bitmap);
	std::vector< Vector3D<uint8_t> > floatToIntBitmap(const std::vector<Vector3DBase>& floatBitmap);
	void saveBitmapToFile(const std::vector< Vector3D<uint8_t> >& bitmap, const std::string& fileName);
	void convertBitmapToJpg(const std::string& fileName, int w, int h);
}