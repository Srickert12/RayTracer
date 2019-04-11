#include "Ray.h"

HitRecord Ray::findIntersection(SurfaceVector & surfaces) {
	HitRecord nearestHit;
	Ray r;
	r.direct = this->direct;
	r.origin = this->origin;

	for (auto surface : surfaces) {
		HitRecord hit = surface->findClosestIntersection(r);

		if (hit.t < nearestHit.t) {
			nearestHit = hit;
		}
	}
	return nearestHit;
}