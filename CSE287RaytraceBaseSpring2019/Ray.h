#pragma once

#include "Defines.h"
#include "Surface.h"

/**
* Simple struct that represents a ray.
*/
struct Ray
{
	dvec3 origin;		// starting point for this ray.
	dvec3 direct;		// direction for this ray, given it's origin.

	Ray( const dvec3 &rayOrigin = dvec3( 0.0, 0.0, 0.0 ), const dvec3 &rayDirection = dvec3( 0.0, 0.0, -1.0 ) ) :
		origin( rayOrigin ), direct( glm::normalize( rayDirection ) )
	{
	}

	HitRecord findIntersection(SurfaceVector & surfaces);

};
