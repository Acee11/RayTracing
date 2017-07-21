#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <iomanip> 

#include "Vector3D.hpp"
#include "Matrix3D.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "Camera.hpp"

constexpr Vector3DBase::basetype EPS = 0.001;

namespace utf = boost::unit_test;

namespace
{
	BOOST_AUTO_TEST_SUITE(Vector3D)

	BOOST_AUTO_TEST_CASE(testcase_plus)
	{
	    BOOST_CHECK(Vector3DBase(1,2,3) + Vector3DBase(1,2,3)  ==  Vector3DBase(2, 4, 6)); 
	}

	BOOST_AUTO_TEST_CASE(testcase_minus)
	{
	    BOOST_CHECK(Vector3DBase(1,2,3) - Vector3DBase(1,2,3)  ==  Vector3DBase(0, 0, 0)); 
	    BOOST_CHECK(Vector3DBase(1,2,3) - Vector3DBase(1,2,3)  ==  Vector3DBase(0)); 
	    BOOST_CHECK(Vector3DBase(1,2,3) - Vector3DBase(1,2,3)  ==  0); 
	}

	BOOST_AUTO_TEST_CASE(testcase_plus_equals)
	{
		Vector3DBase v1(1,2,3);
		Vector3DBase v2(3,4,5);
		v1 += v2;
		BOOST_CHECK(v1  ==  Vector3DBase(4,6,8));
		v2 += v2;
		BOOST_CHECK(v2  ==  Vector3DBase(6,8,10));
	}

	BOOST_AUTO_TEST_CASE(testcase_minus_equals)
	{
		Vector3DBase v1(1,2,3);
		Vector3DBase v2(3,4,5);
		v1 -= v2;
		BOOST_CHECK(v1  ==  Vector3DBase(-2,-2,-2));
		v2 -= v2;
		BOOST_CHECK(v2  ==  Vector3DBase(0,0,0));
	}

	BOOST_AUTO_TEST_CASE(testcase_scalar_operators)
	{
		Vector3DBase v1(1,2,3);
		BOOST_CHECK(v1 * 2.0  ==  Vector3DBase(2, 4, 6));
		BOOST_CHECK(v1 * 2.0  ==  2.0 * v1);
		BOOST_CHECK(v1 / 2.0  ==  Vector3DBase(0.5, 1.0, 1.5));
	}

	BOOST_AUTO_TEST_CASE(testcase_dot, * utf::tolerance(EPS))
	{
		Vector3DBase v1(1,2,3);
		Vector3DBase v2(3,4,5);
		BOOST_CHECK(v1.dot(v2)  ==  26.0);
		BOOST_CHECK(v1.dot(v1)  ==  14.0);
		BOOST_CHECK(v2.dot(v2)  ==  9.0 + 16.0 + 25.0);
	}

	BOOST_AUTO_TEST_CASE(testcase_norm, * utf::tolerance(EPS))
	{
		Vector3DBase v1(1,2,3);
		Vector3DBase v2(3,4,5);
		BOOST_CHECK(fabs(v1.norm() - 3.7416573867739413) < EPS);
		BOOST_CHECK(v1.normalize()  ==  Vector3DBase(0.26726124, 0.53452248, 0.80178373));
		BOOST_CHECK(v1 ==  Vector3DBase(0.26726124, 0.53452248, 0.80178373));
	}

	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE(Matrix3D)

	BOOST_AUTO_TEST_CASE(testcase_constr)
	{
		Matrix3DBase defMat;
		Matrix3DBase zeroMat = 0;
		Matrix3DBase idMat = 1;
		Matrix3DBase copyZeroMat = zeroMat;
		BOOST_CHECK(zeroMat == copyZeroMat);
		BOOST_CHECK(idMat == Matrix3DBase({1,0,0,0,1,0,0,0,1}));
	}

	BOOST_AUTO_TEST_CASE(testcase_mult_mat)
	{
		Matrix3DBase idMat1 = 1;
		Matrix3DBase idMat2 = 1;
		Matrix3DBase zeroMat = 0;
		BOOST_CHECK(idMat1 * idMat2 == idMat1);
		BOOST_CHECK(idMat1 * idMat2 == idMat2 * idMat1);

		Matrix3DBase mat1 = {1,2,3,4,5,6,7,8,9};
		BOOST_CHECK(idMat1 * mat1 == mat1);
		BOOST_CHECK(zeroMat * mat1 == zeroMat);

		mat1 *= mat1;
		BOOST_CHECK(mat1 == Matrix3DBase({30, 36, 42, 66, 81, 96, 102, 126, 150}));
	}

	BOOST_AUTO_TEST_CASE(testcase_mult_matvect)
	{
		Matrix3DBase idMat = 1;
		Vector3DBase v1(1, 0, 0);
		BOOST_CHECK(idMat*v1 == v1);
		idMat *= 2;
		BOOST_CHECK(idMat*v1 == 2*v1);
	}

	BOOST_AUTO_TEST_CASE(testcase_rot_mat)
	{
		Matrix3DBase rotXMat = Matrix3DBase::getXRotation(90.);
		Matrix3DBase rotYMat = Matrix3DBase::getYRotation(90.);
		Matrix3DBase rotZMat = Matrix3DBase::getZRotation(90.);
		Vector3DBase v1(1, 0, 0);
		BOOST_CHECK(rotXMat*v1 == Vector3DBase(1, 0, 0));
		BOOST_CHECK(rotYMat*v1 == Vector3DBase(0, 0, -1));
		BOOST_CHECK(rotZMat*v1 == Vector3DBase(0, 1, 0));
	}

	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE(CameraTest)

	BOOST_AUTO_TEST_CASE(testcase_camera)
	{
		Camera cam{{0,0,-2400}, {0,0,0}, 90.};

		int w = 1920;
		int h = 1080;

		auto view = cam.getView(1920, 1080);

		std::cout << view.frustumTopLeft << std::endl
			<< view.deltaX << std::endl
			<< view.deltaY << std::endl
			<< view.frustumTopLeft + ((float)w)*view.deltaX << std::endl
			<< view.frustumTopLeft + ((float)h)*view.deltaY << std::endl;

		auto topLeftCopy = view.frustumTopLeft;
		for(int i = 0; i < w; ++i)
			topLeftCopy += view.deltaX;
		std::cout << topLeftCopy << std::endl;
	}

	BOOST_AUTO_TEST_SUITE_END()
}