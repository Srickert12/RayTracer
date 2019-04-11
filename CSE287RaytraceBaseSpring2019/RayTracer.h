#pragma once

#include "FrameBuffer.h"
#include "Lights.h"
#include "HitRecord.h"
#include "Surface.h"
#include "Ray.h"

/**
* Class that supports simple ray tracing of a scene containing a number of object 
* (surfaces) and light sources.
*/
class RayTracer
{
	public:

	/**
	* Constructor.
	* @param color buffer to which the ray tracer will be render.
	* @param default color to which pixel will be set when there it no intersection
	* for a ray associated with a particular pixel.
	*/
	RayTracer(FrameBuffer & cBuffer, color defaultColor = color(0.0, 0.0, 0.0, 1.0));

	/**
	* Ray traces a scene containing a number of surfaces and light sources. Sets every
	* pixel in the rendering window. Pixels that are not associated with a ray/surface
	* intersection are set to a default color.
	* @param surfaces - list of the surfaces in the scene
	* @param lights - list of the light sources in the scene
	*/
	void raytraceScene(const SurfaceVector & surfaces, const LightVector & lights);

	/**
	* Sets the w, u, and v orthonormal basis vectors associated with the coordinate
	* frame that is tied to the viewing position and the eye data member of the
	* class.
	* @param viewPosition - xyz position of the view point
	* @param viewingDirection - vector that points in the viewing direction
	* @param up - approximation of the up vector (cannot be parallel to viewing direction)
	*/
	void setCameraFrame(const dvec3 & viewPosition, const dvec3 & viewingDirection, dvec3 up);

	/**
	* Set the following members of the class: topLimit, bottomLimit, rightLimit,
	* leftLimit, distToPlane, nx, and ny based the distance form the middle of
	* the projection plane to the top of the projection plane and width of the
	* rendering window.
	* @param viewPlaneHeight - distance to the top of the projection plane
	*/
	void calculateOrthographicViewingParameters(const double & viewPlaneHeight = 10.0);

	/**
	* Set the following members of the class: topLimit, bottomLimit, rightLimit,
	* leftLimit, distToPlane, nx, and ny based of the specified vertical field of
	* view and height and width of the rendering window.
	* @param verticalFieldOfViewDegrees - vertical field of view in degrees
	*/
	void calculatePerspectiveViewingParameters(const double & verticalFieldOfViewDegrees = 45.0);

	/**
	* Set the color to which pixels are set when the associated ray does not
	* intersect any object in the scene.
	* @param default - color for pixels for which no ray-object intersections occur.
	*/
	void setDefaultColor(color defaultColor) { this->defaultColor = defaultColor; }

	/**
	* Sets the recusion depth to determine how many reflected and refracted bounces for viewing 
	* rays. Values of zero or less result in no reflection of refracted rays being traced.
	* @param recursionDepth - Number of times refracted and reflected rays will be generated 
	* for each view ray.
	*/
	void setRecursionDepth( int recursionDepth ) { this->recursionDepth = recursionDepth; }

	// True to generate rays for perspective viewing. False for orthographic viewing.
	bool renderPerspectiveView = true;
	bool day = true;
protected:

	/**
	* Once the closest point of intersection is found a color is returned based on
	* calculated interactions between the intersected surface and the light
	* sources in the scene.
	*
	* Can be called recursively to trace rays associated with reflection and
	* refraction.
	* @param e - origin of the ray being traced
	* @param d - unit length vector representing the direction of the ray
	* @returns color for the point of intersection
	*/
	color traceIndividualRay( /*const*/ Ray & viewRay, int recursionLevel = 0);
	
	/**
	* Sets the rayOrigin and rayDirection data members of the class based on row and
	* column of a specified pixel.These two data members together represent a
	* parametric description of a ray to be checked for intersection with objects
	* in the scene. The ray is caluclated for a orthographic projection.
	* @param x column of a pixel in the rendering window
	* @param y row of a pixel in the rendering window
	*/
	Ray getOrthoViewRay( const int x, const int y);

	/**
	* Sets the rayOrigin and rayDirection data members of the class based on row and 
	* column of a specified pixel.These two data members together represent a 
	* parametric description of a ray to be checked for intersection with objects
	* in the scene. The ray is caluclated for a perspective projection.
	* @param x column of a pixel in the rendering window
	* @param y row of a pixel in the rendering window
	*/
	Ray getPerspectiveViewRay( const int x, const int y);

	/**
	* Finds the projection plane coordinates, u and v, for the pixel identified
	* by the input arguments.
	* @param x column of a pixel in the rendering window
	* @param y row of a pixel in the rendering window
	* @returns two dimensional vector containing the projection plane coordinates
	*/
	dvec2 getImagePlaneCoordinates(const int x, const int y);

	// Alias for an object controls memory that stores a rgba color value f
	// or every pixel.
	FrameBuffer & colorBuffer;

	// Color to which a pixel is set if there is no intersection
	// for a traced pixel ray.
	color defaultColor;

	// View frame parameters
	dvec3 eye; // position of the viewpoint
	dvec3 u; // "right" relative to the viewing direction
	dvec3 v; //  "up" relative to the viewing vector
	dvec3 w; // camera looks in the negative w direction

	// Projection plane parameters
	// Measured relative to u (right)
	double rightLimit;
	double leftLimit;
	// Measured relative to v (up)
	double topLimit;
	double bottomLimit;

	// Rendering window parameters
	double nx; // Width in pixels
	double ny; // Height in pixel

	// Distance from the viewpoint to the projection plane
	double distToPlane;

	// List of the surfaces in the scene that is being ray traced
	SurfaceVector surfacesInScene;

	// List of the light sources in the scene that is being ray traced
	LightVector lightsInScene;
	
	

	// Max recursion depth
	int recursionDepth;

};


