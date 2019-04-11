#include "ConvexPolygon.h"


ConvexPolygon::ConvexPolygon(std::vector<dvec3> vertices, const color & material)
	: Plane(vertices, material), v(vertices)
{
}

HitRecord ConvexPolygon::findClosestIntersection(const Ray & ray)
{
	HitRecord hitRecord = Plane::findClosestIntersection(ray);
	
	if (checkLeft(v[0], v[1], hitRecord.interceptPoint, hitRecord.surfaceNormal) >= 0
		&& checkLeft(v[1], v[2], hitRecord.interceptPoint, hitRecord.surfaceNormal) >= 0
		&& checkLeft(v[2], v[0], hitRecord.interceptPoint, hitRecord.surfaceNormal) >= 0) {
		return hitRecord;
	}
	else {
		hitRecord.t = FLT_MAX;
		return hitRecord;
	}
	
	return hitRecord;
}

int ConvexPolygon::checkLeft(dvec3 start, dvec3 end, dvec3 p, dvec3 n) {
	return glm::dot(glm::cross(end - start, p - start), n);
}
