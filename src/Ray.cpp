#include "Ray.h"

Vector3DBase Ray::operator () (float t) const
{
	return eye + t * offset;
}