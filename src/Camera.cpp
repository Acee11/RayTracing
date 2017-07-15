#include "Camera.hpp"

Camera::View Camera::getView(int W, int H) const
{
	auto WFloat = static_cast<Vector3DBase::basetype>(W);
	auto HFloat = static_cast<Vector3DBase::basetype>(H);
	Vector3DBase::basetype aovVertical = (HFloat / WFloat) * aov;

	Vector3DBase baseDir(0, 0, 1);

	Matrix3DBase rotLeft = Matrix3DBase::getYRotation(-aov/2.);
	Matrix3DBase rotRight = Matrix3DBase::getYRotation(aov/2.);
	Matrix3DBase rotTop = Matrix3DBase::getXRotation(-aovVertical/2.);
	Matrix3DBase rotBottom = Matrix3DBase::getXRotation(aovVertical/2.);

	Vector3DBase topLeft = (rotTop * rotLeft) * baseDir;
	Vector3DBase topRight = (rotTop * rotRight) * baseDir;
	Vector3DBase bottomLeft = (rotBottom * rotLeft) * baseDir;

	Matrix3DBase frustumRotation = 
		Matrix3DBase::getZRotation(angle.z) *
		Matrix3DBase::getYRotation(angle.y) *
		Matrix3DBase::getXRotation(angle.x);

	topLeft = frustumRotation * topLeft;
	topRight = frustumRotation * topRight;
	bottomLeft = frustumRotation * bottomLeft;

	auto deltaX = (topRight - topLeft)/W;
	auto deltaY = (bottomLeft - topLeft)/H;

	topLeft += location;

	return Camera::View{topLeft, deltaX, deltaY, W, H};
}

Camera Camera::getDefaultCamera()
{
	return Camera{{0,0,0}, {0,0,0}, 75};
}