#ifndef _VECTOR3D_H__
#define _VECTOR3D_H__
#include <cmath>
#include <iostream>

class Vector3D
{
public:
	float x, y, z;

	Vector3D()
	: x(0), y(0), z(0)
	{ }
	Vector3D(float x, float y, float z)
	: x(x), y(y), z(z)
	{ }

	Vector3D operator + (const Vector3D& rhs) const;
	Vector3D& operator += (const Vector3D& rhs);
	Vector3D operator - (const Vector3D& rhs) const;
	Vector3D& operator -= (const Vector3D& rhs);
	Vector3D operator * (const Vector3D& rhs) const;
	Vector3D& operator *= (const Vector3D& rhs);
	Vector3D operator * (float scalar) const;
	friend Vector3D operator * (float scalar, const Vector3D& rhs); 
	Vector3D& operator *= (float rhs);
	Vector3D cross(const Vector3D& rhs) const;
	float dot(const Vector3D& rhs) const;
	float norm() const;
	float normSquared() const;
	void normalize();

	friend std::ostream& operator << (std::ostream& stream, const Vector3D& vect);
};

#endif