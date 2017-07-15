#pragma once

#include "Vector3D.hpp"
#include "Matrix3D.hpp"

class Camera
{
private:
public:
	class View
	{
	public:
		Vector3DBase frustumTopLeft;
		Vector3DBase deltaX;
		Vector3DBase deltaY;
		int width;
		int height;
	};
	Vector3DBase location;
	Vector3DBase angle;
	Vector3DBase::basetype aov;

	View getView(int W, int H) const;
	static Camera getDefaultCamera();
};