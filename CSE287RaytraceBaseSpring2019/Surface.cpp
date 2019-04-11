#include "Surface.h"


Surface::Surface(const color & diffuseColor)
	:	material(Material( diffuseColor ))
{
}

Surface::Surface( const Material & mat )
: material( mat )
{
}

HitRecord Surface::findClosestIntersection( const Ray & ray )
{
	HitRecord hitRecord;
	hitRecord.t = FLT_MAX;

	return hitRecord;
}