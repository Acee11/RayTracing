#include "Ray.h"

Vector3D Ray::operator () (float t) const
{
	return eye + t * offset;
}