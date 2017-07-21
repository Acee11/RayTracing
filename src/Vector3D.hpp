#pragma once
#include <cmath>
#include <iostream>
#include <initializer_list>

template<class T>
class Vector3D
{
public:
	using basetype = T;
	T x, y, z;


	Vector3D<T>() = default;

	Vector3D<T>(T x)
	: Vector3D<T>(x, x, x)
	{}

	Vector3D<T>(T x, T y, T z)
	: x(x), y(y), z(z)
	{}

	Vector3D<T> operator + (const Vector3D<T>& rhs) const
	{
		return Vector3D<T>(
			x + rhs.x,
			y + rhs.y,
			z + rhs.z
		);
	}

	Vector3D<T>& operator += (const Vector3D<T>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vector3D<T> operator - (const Vector3D<T>& rhs) const
	{
		return Vector3D<T>(
			x - rhs.x,
			y - rhs.y,
			z - rhs.z
		);
	}

	Vector3D<T>& operator -= (const Vector3D<T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;

		return *this;
	}

	Vector3D<T> operator * (const Vector3D<T>& rhs) const
	{
		return Vector3D<T>(
			x * rhs.x,
			y * rhs.y,
			z * rhs.z
		);
	}

	Vector3D<T>& operator *= (const Vector3D<T>& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;

		return *this;
	}

	Vector3D<T> operator * (T scalar) const
	{
		return Vector3D<T>(
			x * scalar,
			y * scalar,
			z * scalar
		);
	}

	Vector3D<T>& operator *= (T scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;

		return *this;
	}

	Vector3D<T> operator / (T scalar) const
	{
		return Vector3D<T>(
			x / scalar,
			y / scalar,
			z / scalar
		);
	}

	Vector3D<T>& operator /= (T scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;

		return *this;
	}

	Vector3D<T> operator - () const
	{
		return Vector3D<T>(
			-x,
			-y,
			-z
		);
	}

	bool operator == (const Vector3D<T>& rhs) const
	{
		constexpr T eps = 0.00001;
		return fabs(x - rhs.x) < eps && 
			   fabs(y - rhs.y) < eps && 
			   fabs(z - rhs.z) < eps;
	}

	Vector3D<T> cross(const Vector3D<T>& rhs) const
	{
		return Vector3D<T>(
			y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x
		);
	}

	T dot(const Vector3D<T>& rhs) const
	{
		Vector3D<T> tmp = (*this) * rhs;
		return tmp.x + tmp.y + tmp.z;
	}

	T norm() const
	{
		return sqrt((*this).dot(*this));
	}


	T normSquared() const
	{
		return (*this).dot(*this);
	}

	Vector3D<T>& normalize()
	{
		*this /= norm();
		return *this;
	}

	Vector3D<T> normalized() const
	{
		Vector3D<T> ret = (*this);
		ret.normalize();
		return ret;
	}

	static T distance(Vector3D<T> v1, Vector3D<T> v2)
	{
		return (v1-v2).norm();
	}
	

	friend Vector3D<T> operator * (T scalar, const Vector3D<T>& rhs)
	{
		return Vector3D<T>(
			rhs.x * scalar,
			rhs.y * scalar,
			rhs.z * scalar
		);
	}

	friend std::ostream& operator<< (std::ostream& stream, const Vector3D<T>& vect)
	{
		stream << '[' << vect.x << ", " << vect.y << ", " << vect.z << "]";
		return stream;
	}

};
using Vector3DBase = Vector3D<float>;
