#pragma once

#include "Surface.h"

/**
* Sub-class of Surface that represents inplicit description of a sphere.
*/
class Sphere : 	public Surface
{
	public:

	/**
	* Constructor for the sphere.
	* @param - point: specifies an xyz position of the center of the sphere
	* @param - radius: radius of the sphere
	* @param - material: color of the plane.
	*/
	Sphere(const dvec3 & position = dvec3(0.0, 0.0, -5.0),
			double radius = 1.0, 
			const color & material = color(1.0, 1.0, 1.0, 1.0) );

	Sphere(const dvec3 & position = dvec3(0.0, 0.0, -5.0),
		double radius = 1.0,
		const Material & material = Material(LIGHT_GRAY));
	/**
	* Checks a ray for intersection with the surface. Finds the closest point of intersection
	* if one exits. Returns a HitRecord with the t parmeter set to FLT_MAX if there is no
	* intersection.
	* @param rayOrigin - Origin of the ray being check for intersetion
	* @param rayDirection - Unit vector represention the direction of the ray.
	* returns HitRecord containing intormation about the point of intersection.
	*/
	virtual HitRecord findClosestIntersection( const Ray & ray );

	/**
	* Radius of the sphere
	*/
	double radius;

	/**
	* xyz location of the center of the sphere
	*/
	dvec3 center;
};

