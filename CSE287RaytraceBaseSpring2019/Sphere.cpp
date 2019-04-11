#include "Sphere.h"


Sphere::Sphere(const dvec3 & position, double radius, const color & material)
	: Surface(material), center(position), radius(radius)
{
}

Sphere::Sphere(const dvec3 & position, double radius, const Material & material)
	: Surface(material), center(position), radius(radius)
{
}

/*
* Checks a ray for intersection with the surface. Finds the closest point of intersection
* if one exits. Returns a HitRecord with the t parmeter set to FLT_MAX if there is no
* intersection.
*/
HitRecord Sphere::findClosestIntersection( const Ray & ray )
{
	HitRecord hitRecord;

	// Calculate the discriminant to determine if there are any intersections.
	double discriminant = pow(glm::dot(ray.direct, ray.origin - center), 2) - dot(ray.direct, ray.direct)*(glm::dot(ray.origin - center, ray.origin - center) - radius * radius);

	if( discriminant >= 0 ) {

		double t = FLT_MAX;

		if( discriminant > 0 ) {

			// Two intercepts. Find and return the closest one.
			double t1 = (glm::dot(-ray.direct, ray.origin - center) - sqrt(discriminant)) / dot(ray.direct, ray.direct);
			double t2 = (glm::dot(-ray.direct, ray.origin - center) + sqrt(discriminant)) / dot(ray.direct, ray.direct);
	
			if (t1 < 0) {
				t1 = FLT_MAX;
			}
			if (t2 < 0) {
				t2 = FLT_MAX;
			}

			if (t1 < t2) {

				t = t1;
			}
			else {

				t = t2;
			}
		}
		else {
			// One Intercept. Find and return the t for the single point of intersection.
			t = glm::dot(-ray.direct, ray.origin - center) / dot(ray.direct, ray.direct);
			if (t < 0) {
				t = FLT_MAX;
			}
		}

		// Set hit record information about the intersetion.
		hitRecord.t = t;
		hitRecord.interceptPoint = ray.origin + t * ray.direct;
		
		dvec3 n = glm::normalize(hitRecord.interceptPoint - center);
		
		// Check for back face intersection
		if (glm::dot(n, ray.direct) > 0) {

			n = -n; // reverse the normal
		}

		hitRecord.surfaceNormal = n;
		hitRecord.material = material;
	}
	else {
		// Set parameter, t, in the hit record to indicate "no intersection."
		hitRecord.t = FLT_MAX;
	}

	return hitRecord;

} // end findClosestIntersection