#pragma once
#include "QuadricSurface.h"
class Ellipsoid :
	public QuadricSurface
{
public:
	Ellipsoid(const dvec3 & position, const color & mat);
	Ellipsoid(const dvec3 & position, const Material & mat);
	virtual HitRecord findClosestIntersection(const Ray & ray);
	dvec3 center;
	double a, b, c;
};

