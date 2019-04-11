#pragma once

#include "HitRecord.h"
#include "Ray.h"
#include "Material.h"

/** 
* Super class for all implicitly described surfaces in a scene. Support intersection testing
* with rays.
*/
class Surface
{
public:

	/**
	* Constructor for the surface.
	* @param - diffuseColor: diffuse color of the surface.
	*/
	Surface(const color & diffuseColor);

	/**
	* Constructor for the surface.
	* @param - material: material properies of the surface.
	*/
	Surface( const Material & mat );

	/**
	* Checks a ray for intersection with the surface. Finds the closest point of intersection
	* if one exits. Returns a HitRecord with the t parmeter set to FLT_MAX if there is no
	* intersection.
	* @param rayOrigin - Origin of the ray being check for intersetion
	* @param rayDirection - Unit vector represention the direction of the ray.
	* returns HitRecord containing intormation about the point of intersection.
	*/
	virtual HitRecord findClosestIntersection(const struct Ray & ray);

	/**
	* Color of the surface
	*/
	Material material;

protected:

	virtual glm::dvec2 calculateSphericalTextureCoordinates(/*??*/){ return glm::dvec2(0.0, 0.0); };

	virtual glm::dvec2 calculatePlanarTextureCoordinates(/*??*/){ return glm::dvec2(0.0, 0.0); };

	virtual glm::dvec2 calculateCylindricalTextureCoordinates(/*??*/){ return glm::dvec2(0.0, 0.0); };

};

