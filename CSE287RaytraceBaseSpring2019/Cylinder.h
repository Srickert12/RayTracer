#pragma once
#include "QuadricSurface.h"
class Cylinder :
	public QuadricSurface
{
public:
	Cylinder(const dvec3 & position, const color & mat);
	Cylinder(const dvec3 & position, const Material & mat);
	virtual HitRecord findClosestIntersection(const Ray & ray);
};

