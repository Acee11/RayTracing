#include "Vector3D.h"

Vector3D Vector3D::operator + (const Vector3D& rhs) const
{
	return Vector3D(
		x + rhs.x,
		y + rhs.y,
		z + rhs.z
	);
}
Vector3D& Vector3D::operator += (const Vector3D& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

Vector3D Vector3D::operator - (const Vector3D& rhs) const
{
	return Vector3D(
		x - rhs.x,
		y - rhs.y,
		z - rhs.z
	);
}
Vector3D& Vector3D::operator -= (const Vector3D& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

Vector3D Vector3D::operator * (const Vector3D& rhs) const
{
	return Vector3D(
		x * rhs.x,
		y * rhs.y,
		z * rhs.z
	);
}

Vector3D& Vector3D::operator *= (const Vector3D& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;

	return *this;
}

Vector3D Vector3D::operator * (float scalar) const
{
	return Vector3D(
		x * scalar,
		y * scalar,
		z * scalar
	);
}

Vector3D operator * (float scalar, const Vector3D& rhs)
{
	return Vector3D(
		rhs.x * scalar,
		rhs.y * scalar,
		rhs.z * scalar
	);
}

Vector3D& Vector3D::operator *= (float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

Vector3D Vector3D::cross(const Vector3D& rhs) const
{
	return Vector3D(
		y * rhs.z - z * rhs.y,
		z * rhs.x - x * rhs.z,
		x * rhs.y - y * rhs.x
	);
}

float Vector3D::dot(const Vector3D& rhs) const
{
	Vector3D tmp = (*this) * rhs;
	return tmp.x + tmp.y + tmp.z;
}

float Vector3D::norm() const
{
	return sqrt((*this).dot(*this));
}

float Vector3D::normSquared() const
{
	return (*this).dot(*this);
}

void Vector3D::normalize()
{
	float vectNorm = norm();
	x /= vectNorm;
	z /= vectNorm;
	y /= vectNorm;
}

std::ostream& operator << (std::ostream& stream, const Vector3D& vect)
{
	stream << '[' << vect.x << ", " << vect.y << ", " << vect.z << "]";
	return stream;
}
