#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <iomanip> 

#include "Vector3D.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "ArrayScene.hpp"

#define EPS 0.001

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
		BOOST_CHECK(abs(v1.norm() - 3.7416573867739413) < EPS);
		BOOST_CHECK(v1.normalize()  ==  Vector3DBase(0.26726124, 0.53452248, 0.80178373));
		BOOST_CHECK(v1 ==  Vector3DBase(0.26726124, 0.53452248, 0.80178373));
		BOOST_CHECK(v2.dot(v2)  ==  9.0 + 16.0 + 25.0);
	}

	BOOST_AUTO_TEST_SUITE_END()
}


/*
int main()
{
	Vector3DBase v1(1, 2, 3), v2(4, 5, 6);
	std::cout << "Vector3D tests:" << std::endl;
	std::cout <<  v1 + v2 << " = [5, 7, 9]" << std::endl;
	std::cout <<  v1 - v2 << " = [-3,-3, -3]" << std::endl;
	std::cout <<  v1 * v2 << " = [4, 10, 18]" << std::endl;
	std::cout <<  v1 + v2 << " = [5, 7 9]" << std::endl;
	std::cout << std::fixed << std::setprecision(4) << v1.dot(v2) << " =~ 32" << std::endl;
	std::cout << std::fixed << std::setprecision(4) << v1.norm() << " =~ 3.741" << std::endl;
	std::cout << std::fixed << std::setprecision(4) << v1.normSquared() << " = 14" << std::endl;
	std::cout << std::fixed << std::setprecision(4) << 2 * v1 << 
		" = " << v1 * 2 << " = [2, 4, 9]" << std::endl;

	Sphere s1({0, 0, 3}, 2), s2({0,2,3}, 2);
	Ray r1({0, 0,-10 }, {0, 0, 1});
	std::cout << "Sphere intersection tests:" << std::endl;
	std::cout << s1.getIntersectionPoint(r1) << " = [0, 0, 1]" << std::endl;
	std::cout << s2.getIntersectionPoint(r1) << " = [0, 0, 3]" << std::endl;

	Ray r2({0, 0, 3}, {0, 0, 1});
	std::cout << s1.getIntersectionPoint(r2) << " = [0, 0, 5]" << std::endl;


	ArrayScene scene;
	scene.addObject(new Sphere({0, 0, 3}, 2));
	scene.addObject(new Sphere({5, 5, 5}, 1));
	scene.addObject(new Sphere({-5, -5, 10}, 2));
	scene.addObject(new Sphere({0, 0, 7}, 2));

	Ray r({0, 0,-10 }, {0, 0, 1});

	auto ret = scene.getIntersectingObject(r);
	ret.first.print();
	std::cout << "  |  " << ret.second << std::endl;
}
*/