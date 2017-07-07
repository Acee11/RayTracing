#include <iostream>
#include <iomanip> 

#include "Vector3D.h"
#include "Sphere.h"
#include "Ray.h"
#include "ArrayScene.h"


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