#include "Polygon.h"


Polygon::Polygon(std::vector<dvec3> vertices, const color & material)
	: Plane(vertices, material), v(vertices)
{
}

HitRecord Polygon::findClosestIntersection(const Ray & ray)
{
	HitRecord hitRecord = Plane::findClosestIntersection(ray);
	if (checkLeft(v[0], v[1], hitRecord.interceptPoint, hitRecord.surfaceNormal) > 0
		&& checkLeft(v[1], v[2], hitRecord.interceptPoint, hitRecord.surfaceNormal) > 0
		&& checkLeft(v[0], v[1], hitRecord.interceptPoint, hitRecord.surfaceNormal) > 0) {
		return hitRecord;
	}
	else {
		hitRecord.t = FLT_MAX;
		return hitRecord;
	}
}

int Polygon::checkLeft(dvec3 v1, dvec3 v2, dvec3 p, dvec3 n) {
	return glm::dot(glm::cross(v2 - v1, p - v1), n);
}
