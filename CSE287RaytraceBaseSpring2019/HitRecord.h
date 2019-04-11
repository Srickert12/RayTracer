#pragma once

#include "Defines.h"
#include "Material.h"

/**
* Simple struct to hold information about points of intersection.
*/
struct HitRecord {

	HitRecord(){ t = FLT_MAX; }

	glm::dvec3 interceptPoint; // xyz location of intersection

	glm::dvec2 textureCoordinates; // 2D texture coordinates for point of intersection.

	glm::dvec3 surfaceNormal; // surface normal at the point of intersection

	Material material; // Color of the surface

	double t; // Paremeter in parametric a ray at point of intersectopm

};