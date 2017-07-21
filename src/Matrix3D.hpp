#pragma once

#include <initializer_list>
#include <cmath>

template<class T>
class Matrix3D
{
private:
	inline static T degToRadian(T deg) //TODO move this somewhere else
	{
		return (M_PI/180.) * deg;
	}
public:
	using basetype = T;
	

	Matrix3D<T>() = default;

	Matrix3D<T>(T val)
	{
		for(int i = 0; i < 3; ++i)
			for(int j = 0; j < 3; ++j)
				mat[i][j] = i == j ? val : 0;
	}

	//Matrix3D<T>(const Matrix3D<T>& rhs) = default;

	Matrix3D<T>(const std::initializer_list<T>& initList)
	{
		if(initList.size() != 9)
			throw std::length_error("length not 9");
		int cnt = 0;
		for(int i = 0; i < 3; ++i)
			for(int j = 0; j < 3; ++j)
				mat[i][j] = *(initList.begin() + cnt++);
	}
	Matrix3D<T> operator * (const Matrix3D<T>& rhs) const
	{
		Matrix3D<T> result;
		for(int i = 0; i < 3; ++i)
			for(int j = 0; j < 3; ++j)
				result.mat[i][j] = 
					mat[i][0] * rhs.mat[0][j] +
					mat[i][1] * rhs.mat[1][j] +
					mat[i][2] * rhs.mat[2][j];
		return result;
	}

	Matrix3D<T>& operator *= (const Matrix3D<T>& rhs)
	{
		*this = *this * rhs;
		return *this;
	}

	Vector3D<T> operator * (const Vector3D<T>& rhs)
	{
		return Vector3D<T>(
			rhs.dot({mat[0][0], mat[0][1], mat[0][2]}),
			rhs.dot({mat[1][0], mat[1][1], mat[1][2]}),
			rhs.dot({mat[2][0], mat[2][1], mat[2][2]})
		);
	}

	bool operator == (const Matrix3D<T>& rhs) const
	{
		constexpr T eps = 0.00001;
		for(int i = 0; i < 3; ++i)
			for(int j = 0; j < 3; ++j)
				if(fabs(mat[i][j] - rhs.mat[i][j]) > eps)
					return false;
		return true;
	}

	

	static Matrix3D<T> getXRotation(T deg)
	{
		T degRad = degToRadian(deg);
		T sinDeg = sin(degRad);
		T cosDeg = cos(degRad);
		return Matrix3D<T>({
			1,      0,       0,
			0,    cosDeg, -sinDeg,
			0,    sinDeg,  cosDeg 
		});
	}

	static Matrix3D<T> getYRotation(T deg)
	{
		T degRad = degToRadian(deg);
		T sinDeg = sin(degRad);
		T cosDeg = cos(degRad);
		return Matrix3D<T>({
			cosDeg,   0,   sinDeg,
			   0,     1,     0,
			-sinDeg,  0,   cosDeg 
		});
	}

	static Matrix3D<T> getZRotation(T deg)
	{
		T degRad = degToRadian(deg);
		T sinDeg = sin(degRad);
		T cosDeg = cos(degRad);
		return Matrix3D<T>({
			cosDeg,  -sinDeg,     0,
			sinDeg,   cosDeg,     0,
			  0,        0,        1 
		});
	}

	T mat[3][3];

};

using Matrix3DBase = Matrix3D<float>;