#include "Ellipsoid.h"



Ellipsoid::Ellipsoid(const dvec3 & position, const color & mat)
	: QuadricSurface(position, mat), center(center)
{
	A = glm::pow(1 - position.x, 2) / 4.0;
	B = glm::pow(1 - position.y, 2) / 9.0;
	C = glm::pow(1 - position.z, 2) / 25.0;
	D = 0;
	E = 0;
	F = 0;
	G = 0;
	H = 0;
	I = 0;
	J = -1;

}

Ellipsoid::Ellipsoid(const dvec3 & position, const Material & mat)
	: QuadricSurface(position, mat)
{}

HitRecord Ellipsoid::findClosestIntersection(const Ray & ray) {
	HitRecord hitRecord = QuadricSurface::findClosestIntersection(ray);
	return hitRecord;
}
