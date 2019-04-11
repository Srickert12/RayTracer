#include "RayTracer.h"


RayTracer::RayTracer(FrameBuffer & cBuffer, color defaultColor )
:colorBuffer(cBuffer), defaultColor(defaultColor), recursionDepth(2)
{
	
}


void RayTracer::setCameraFrame(const dvec3 & viewPosition, const dvec3 & viewingDirection, dvec3 up)
{
	// TODO
	w = glm::normalize(-viewingDirection);
	u = glm::normalize(glm::cross(up, w));
	v = glm::normalize(glm::cross(w, u));
} // end setCameraFrame


void RayTracer::calculatePerspectiveViewingParameters(const double & verticalFieldOfViewDegrees)
{

	// TODO
	topLimit = 1;
	rightLimit = topLimit * ((double)colorBuffer.getWindowWidth() / colorBuffer.getWindowHeight());
	leftLimit = -rightLimit;
	bottomLimit = -topLimit;

	nx = (double)colorBuffer.getWindowWidth();
	ny = (double)colorBuffer.getWindowHeight();

	distToPlane = topLimit / (glm::tan(verticalFieldOfViewDegrees / 2));

	renderPerspectiveView = true; // generate perspective view rays
	
} // end calculatePerspectiveViewingParameters


void RayTracer::calculateOrthographicViewingParameters(const double & viewPlaneHeight)
{
	topLimit = fabs(viewPlaneHeight) / 2.0;

	rightLimit = topLimit * ((double)colorBuffer.getWindowWidth()/colorBuffer.getWindowHeight()); // Set r based on aspect ratio and height of plane

	// Make view plane symetrical about the viewing direction
	leftLimit = -rightLimit; 
	bottomLimit = -topLimit;

	// Calculate the distance between pixels in the horizontal and vertical directions
	nx = (double)colorBuffer.getWindowWidth();
	ny = (double)colorBuffer.getWindowHeight();

	distToPlane = 0.0; // Rays start on the view plane

	renderPerspectiveView = false; // generate orthographic view rays
	
} // end calculateOrthographicViewingParameters


void RayTracer::raytraceScene(const SurfaceVector & surfaces, const LightVector & lights)
{
	this->surfacesInScene = surfaces;
	this->lightsInScene = lights;

	// Iterate through each and every pixel in the rendering window
	// TODO
	for (int y = 0; y < colorBuffer.getWindowHeight(); y++) {
		for (int x = 0; x < colorBuffer.getWindowWidth(); x++) {
			if (renderPerspectiveView == true) {
				Ray r = getPerspectiveViewRay(x, y);
				color c = traceIndividualRay(r, 3);
				colorBuffer.setPixel(x, y, c);
			}
			else {
				Ray r = getOrthoViewRay(x, y);
				color c = traceIndividualRay(r, 3);
				colorBuffer.setPixel(x, y, c);
			}
		}
	}
} // end raytraceScene



color RayTracer::traceIndividualRay(/*const*/ Ray & viewRay, int recursionLevel)
{
	// Find surface intersection that is closest to 'e' in the direction 'd.'
	// TODO
	
	HitRecord nearestHit;
	
	nearestHit = viewRay.findIntersection(surfacesInScene);

	if (nearestHit.t < FLT_MAX) {
		
		color totalLight = nearestHit.material.emissive;
		
		for( auto light : lightsInScene ) {
			totalLight += light->illuminate( -viewRay.direct, nearestHit, surfacesInScene );

		}


		if (recursionLevel == 0) {
			return totalLight;
		}
		else {
			Ray reflection(nearestHit.interceptPoint + nearestHit.surfaceNormal * EPSILON, glm::reflect(viewRay.direct, nearestHit.surfaceNormal));
			totalLight += 0.2 * traceIndividualRay( reflection, recursionLevel - 1);
		}

		
		return totalLight;
	}
	else {
		if (day) {
			return LIGHT_BLUE;
		}
		else {
			return 0.5 * LIGHT_BLUE;
		}
	}
	

} // end traceRay


Ray RayTracer::getOrthoViewRay( const int x, const int y)
{
	Ray orthoViewRay;

	dvec2 uv = getImagePlaneCoordinates(x, y);
	
	orthoViewRay.origin = eye + uv.x * u + uv.y * v;
	orthoViewRay.direct = glm::normalize( -w );

	return orthoViewRay;

} // end getOrthoViewRay


Ray RayTracer::getPerspectiveViewRay(const int x, const int y)
{
	Ray perspectiveViewRay;

	// TODO
	perspectiveViewRay.origin = eye;

	dvec2 uv = getImagePlaneCoordinates(x, y);
	perspectiveViewRay.direct = glm::normalize(-distToPlane * w + uv.x * u + uv.y * v);
	return perspectiveViewRay;

} // end getPerspectiveViewRay


dvec2 RayTracer::getImagePlaneCoordinates(const int x, const int y)
{

	dvec2 uv;
	// TODO

	uv.x = leftLimit + (rightLimit - leftLimit) * ((x + 0.5) / nx);
	uv.y = bottomLimit + (topLimit - bottomLimit) * ((y + 0.5) / ny);

	return uv;
}





