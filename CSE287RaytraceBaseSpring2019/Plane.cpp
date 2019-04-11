#include "Plane.h"

/**
* Constructor for the Plane.
*/
Plane::Plane(const dvec3 & point, const dvec3 & normal, const color & material)
	: Surface(material), a(point), n(normalize(normal))
{
}

Plane::Plane(std::vector<dvec3> vertices, const color & material)
	: Surface(material)
{
	a = vertices[0];

	n = glm::normalize(glm::cross(vertices[2] - vertices[1], vertices[0] - vertices[1]));
}


/*
* Checks a ray for intersection with the surface. Finds the closest point of intersection
* if one exits. Returns a HitRecord with the t parmeter set to FLT_MAX if there is no
* intersection.
*/
HitRecord Plane::findClosestIntersection( const Ray & ray )
{
	HitRecord hitRecord;
	double t;

	// TODO
	if (glm::dot(ray.direct, n) == 0) {
		t = FLT_MAX;
		return hitRecord;
	} 
	t = glm::dot(a - ray.origin, n) / glm::dot(ray.direct, n);
	if (t>=0) {
		hitRecord.t = t;
		hitRecord.interceptPoint = ray.origin + t * ray.direct;
		if (glm::dot(ray.direct, n) >= 0) {
			hitRecord.surfaceNormal = -n;
		}
		else {
			hitRecord.surfaceNormal = n;
		}
		hitRecord.material = material;
	}
	else {
		t = FLT_MAX;
	}
	
	return hitRecord;

} // end findClosestIntersection

