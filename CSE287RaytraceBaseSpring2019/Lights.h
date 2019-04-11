#pragma once

#include "Defines.h"
#include "HitRecord.h"
#include "Surface.h"
#include "Ray.h"

HitRecord findIntersection( const Ray & ray, SurfaceVector & surfaces );


/**
* Base struct for all types of lights. Supports only specification of the 
* color and intensity of light sources. Parent of sub-structs that simulate
* positional, directional, and spot lights.
*
* Instances of this struct an be used to simulate only ambient light. Ambient
* light is described as bounced light that has been scattered so much that it
* is impossible to tell the direction to its source. If using a LightSource 
* instantiation to simulate ambient light, the overall intensity of the light
* should be low in order to avoid washing out shadows as well as diffuse and 
* specular effects that can be achieved when using children of this struct.
*/
struct LightSource
{
	LightSource(const color & lightColor) 
	: diffuseLightColor(lightColor)
	{
		ambientLightColor = 0.25 * diffuseLightColor;
		specularLightColor = WHITE;
	}

	virtual color illuminate(const dvec3 & eyeVector, HitRecord & closestHit, SurfaceVector & surfaces)
	{
		if (enabled) {
			return ambientLightColor * closestHit.material.ambientColor;
		}
		else {
			return BLACK;
		}
	}

	bool enabled = true;
	bool day = true;

	/*
	* Ambient color and intensity of the light.
	*/
	color ambientLightColor;

	/* 
	* Diffuse color and intensity of the light.
	*/
	color diffuseLightColor; 

	/*
	 * Specular color and intensity of the light.
	 */
	color specularLightColor;
};

/**
* Struct for simulating light sources that have an explicit position and 
* shine equally in all directions. Instantiations of the struct will have
* a position property and a color and intensity of the light given off
* by the light.
*/
struct PositionalLight : public LightSource
{
	PositionalLight(glm::dvec3 position, const color & lightColor)
	: LightSource(lightColor), lightPosition(position)
	{}

	virtual color illuminate(const glm::dvec3 & eyeVector, HitRecord & closestHit, SurfaceVector & surfaces)
	{
		if (enabled) {
			dvec3 lightVector = glm::normalize(lightPosition - closestHit.interceptPoint);

			dvec3 reflectionVector = glm::normalize(glm::reflect(-lightVector, closestHit.surfaceNormal));

			Ray shadowRay(closestHit.interceptPoint + closestHit.surfaceNormal * EPSILON, lightVector);

			HitRecord shadowHit = shadowRay.findIntersection(surfaces);

			color totalLight = BLACK;

			if (shadowHit.t > glm::length( lightPosition - closestHit.interceptPoint )) {

				totalLight += (LightSource::illuminate(eyeVector, closestHit, surfaces));
				totalLight += glm::max(glm::dot(lightVector, closestHit.surfaceNormal), 0.0) * diffuseLightColor * closestHit.material.diffuseColor;
				totalLight += glm::pow(glm::max(0.0, glm::dot(eyeVector, reflectionVector)), closestHit.material.shininess) * specularLightColor * closestHit.material.specularColor;
			}
			else {
				return BLACK;
			}
			if (day) {
				return totalLight;
			}
			else {
				return totalLight * 0.3;
			}
		}
		else {
			return BLACK;
		}
	}


	/**
	* x, y, z position of the light source. 
	*/
	glm::dvec3 lightPosition; 
};

/**
* Struct for simulating light sources that do not have an explicit position.
* Such light sources have only a direction against which they are shinning.
* Instantiations of the struct will have this direction properties along with
* a color and intensity of the light given off by the light source.
*/
struct DirectionalLight : public LightSource
{
	DirectionalLight(dvec3 direction, const color & lightColor)
	: LightSource(lightColor), lightDirection(glm::normalize(direction))
	{}

	virtual color illuminate(const dvec3 & eyeVector, HitRecord & closestHit, SurfaceVector & surfaces)
	{
		if (enabled) {

			dvec3 lightVector = lightDirection;

			dvec3 reflectionVector = glm::normalize(glm::reflect(-lightVector, closestHit.surfaceNormal));
			
			color totalLight = BLACK;

			Ray shadowRay( closestHit.interceptPoint + closestHit.surfaceNormal * EPSILON, lightVector);
			HitRecord shadowHit = shadowRay.findIntersection(surfaces);

			if (shadowHit.t == FLT_MAX) {
				totalLight += (LightSource::illuminate(eyeVector, closestHit, surfaces));
				totalLight += glm::max(glm::dot(lightVector, closestHit.surfaceNormal), 0.0) * diffuseLightColor * closestHit.material.diffuseColor;
				totalLight += glm::pow(glm::max(0.0, glm::dot(eyeVector, reflectionVector)), closestHit.material.shininess) * specularLightColor * closestHit.material.specularColor;
			}
			else {
				totalLight += (LightSource::illuminate(eyeVector, closestHit, surfaces));
			}
			if (day) {
				return totalLight;
			}
			else {
				return totalLight * 0.3;
			}
		}
		else {
			return BLACK;
		}
	}

	/**
	* Unit vector that points in the direction that is opposite 
	* the direction in which the light is shining.
	*/
	glm::dvec3 lightDirection; 
	
};

/**
* Struct for simulating light sources that have an explicit position
* and shine in a specified direction.Width of the associated beam of
* light is controlled using a spot cutoff cosine. Instantiations
* of the struct will have position and direction properties along with
* a color and intensity of the light given off by the light source.
*/

struct SpotLight : public PositionalLight
{
	SpotLight(dvec3 position, dvec3 direction,
		float cutOffCosineRadians, const color & colorOfLight)
		: PositionalLight(position, colorOfLight),
		spotDirection(glm::normalize(direction)),
		cutOffCosineRadians(cutOffCosineRadians)
	{
	}

	virtual color illuminate(const glm::dvec3 & eyeVector,
		HitRecord & closestHit,
		SurfaceVector & surfaces)
	{
		double spotCosine = glm::dot(spotDirection, -glm::normalize(lightPosition - closestHit.interceptPoint));
		if (spotCosine > (cutOffCosineRadians)) {
			double falloff = 1 - (1 - spotCosine) / (1 - (cutOffCosineRadians));
			return falloff * PositionalLight::illuminate(eyeVector, closestHit, surfaces);
		}
		else {
			return BLACK;
		}
	}

	/**
	* Unit vector that points in the direction in which the light
	* is shining.
	*/
	dvec3 spotDirection;

	/**
	* Angle in radians of half the spot light beam
	*/
	double cutOffCosineRadians;

};


