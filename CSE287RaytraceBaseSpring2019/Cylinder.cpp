#include "Cylinder.h"



Cylinder::Cylinder(const dvec3 & position, const color & mat) :
	QuadricSurface(position, mat)
{
	A = glm::pow(1-position.x, 2) / 4;
	B = 0;
	C = glm::pow(1 - position.x, 2) / 4;
	D = 0;
	E = 0;
	F = 0;
	G = 0;
	H = 0;
	I = 0;
	J = -1;
}

Cylinder::Cylinder(const dvec3 & position, const Material &mat) :
	QuadricSurface(position, mat)
{

}

HitRecord Cylinder::findClosestIntersection(const Ray & ray) {
	HitRecord hitRecord = QuadricSurface::findClosestIntersection(ray);
	return hitRecord;
}


