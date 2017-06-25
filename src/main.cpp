#include <iostream>

#include "Vector3D.h"
#include "Sphere.h"
#include "Ray.h"

int main()
{
	Vector3D vect1(1.0, 2.0, 3.0);
	std::cout << "Test 1:\n" << vect1.norm() << std::endl;

	Vector3D vect2(2.0, 2.5, 3.0);
	std::cout << "Test 2:\n" << vect1 + vect2 << std::endl << vect1 * vect2 << std::endl;
	vect1 += vect2;
	vect2 *= vect2;
	std::cout << "Test 3:\n" << vect1 << std::endl << vect2 << std::endl;

	vect1.normalize();
	std::cout << "Test 4:\n" << vect1 << std::endl << vect1.norm() << std::endl;

	std::cout << "Test 5:\n" << vect1.dot(vect1.cross(vect2)) << std::endl;

	std::cout << "Test 5:\n" << vect1 << std::endl << vect1 * 2.0 << std::endl << 
		2.0 * vect1 << std::endl;

	Sphere sphere(Vector3D(0,5,100), 5);
	Ray ray(Vector3D(0, 0, -100), Vector3D(0,0,1));
	std::cout << "Test 6:\n" << sphere.getIntersectionPoint(ray) << std::endl;
	
	return 0;
}