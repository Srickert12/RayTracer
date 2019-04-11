#include "FrameBuffer.h"

/**
* Constructor. Allocates memory for storing pixel values.
*/
FrameBuffer::FrameBuffer(const int width, const int height)
{
	setFrameBufferSize(width, height);

} // end FrameBuffer constructor


/**
* Deallocates dynamically memory associated with the class.
*/
FrameBuffer::~FrameBuffer(void)
{
	// Free the memory associated with the color buffer
	delete[] colorBuffer;
	delete[] depthBuffer;

} // end FrameBuffer destructor


/**
* Sizes the color buffer to match the window size. Deallocates any
* memory that was previsouly allocated.
*/
void FrameBuffer::setFrameBufferSize(const int width, const int height) {

	// Save the dimensions of the window
	window.width = width;
	window.height = height;

	// Set pixel storage modes. 
	// (https://www.opengl.org/archives/resources/features/KilgardTechniques/oglpitfall/)
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);

	// Free the memory previously associated with the color buffer
	delete[] colorBuffer;
	delete[] depthBuffer;

	// Allocate the color buffer to match the size of the window
	colorBuffer = new GLubyte[width*BYTES_PER_PIXEL*height];
	depthBuffer = new float[width*height];

} // end setFrameBufferSize


/**
* Sets the color to which the window will be cleared. Does NOT
* actually clear the window
*/
void FrameBuffer::setClearColor(const color & clear) {

	clearColor[0] = (GLubyte)(clear.r * 255.0);
	clearColor[1] = (GLubyte)(clear.g * 255.0);
	clearColor[2] = (GLubyte)(clear.b * 255.0);
	clearColor[3] = (GLubyte)(clear.a * 255.0);

} // end setClearColor


/**
* Clears the window to the clear color.
*/
void FrameBuffer::clearColorAndDepthBuffers() {

	for (int y = 0; y < window.height; ++y) {
		for (int x = 0; x < window.width; ++x) {

			std::memcpy(colorBuffer + BYTES_PER_PIXEL * (x + y * window.width),
				clearColor, BYTES_PER_PIXEL);
			depthBuffer[y * window.width + x] = 1.0;
		}
	}

} // end clearFrameBuffer


/**
* Copies memory into frame buffer and updates the window
* using an OpenGL command.
*/
void FrameBuffer::showColorBuffer()
{
	// Insure raster position is lower left hand corner of the window. (OpenGL command)
	glRasterPos2d(-1, -1);

	// Copy color buffer to raster (Legacy OpenGL command)
	glDrawPixels(window.width, window.height, GL_RGBA, GL_UNSIGNED_BYTE, colorBuffer);

	// Flush all drawing commands and swapbuffers (Glut command)
	glutSwapBuffers();

} // end showFrameBuffer



bool FrameBuffer::checkInWindow(const int & x, const int & y)
{
	if (0 <= x && x < window.width && 0 <= y && y < window.height) {

		return true;
	}
	else {
		return false;
	}

} // end checkInWindow


/**
* Sets an individual pixel value in the color buffer. Origin (0,0)
* is the lower left hand corner of the window.
*/
void FrameBuffer::setPixel(const int x, const int y, const color & rgba) {

	if ( checkInWindow(x, y) == true ) {

		color clampedColor = glm::clamp(rgba, 0.0, 1.0);

		GLubyte c[] = { (GLubyte)(clampedColor.r * 255),
			(GLubyte)(clampedColor.g * 255),
			(GLubyte)(clampedColor.b * 255),
			(GLubyte)(clampedColor.a * 255) };

		std::memcpy(colorBuffer + BYTES_PER_PIXEL * (x + y * window.width), c, BYTES_PER_PIXEL);
	}

} // end setPixel


/**
* Returns the stored RGBA color valute for an individual pixel position
* in the color buffer. Origin (0,0) is the lower left hand corner
* of the window.
*/
color FrameBuffer::getPixel(const int x, const int y)
{
	if (checkInWindow(x, y) == true) {

		GLubyte c[BYTES_PER_PIXEL];

		// Retrieve color values from the color buffer
		std::memcpy(c, colorBuffer + BYTES_PER_PIXEL * (x + y * window.width), BYTES_PER_PIXEL);

		// Convert individual color components back to floating point values
		double red = c[0]/ 255.0;
		double green = c[1] / 255.0;
		double blue = c[2] / 255.0;
		double alpha = c[3] / 255.0;

		return color(red, green, blue, alpha);

	}
	else {

		return color(clearColor[0] / 255.0, clearColor[1] / 255.0, clearColor[2] / 255.0, clearColor[3] / 255.0 );
	}

} // end getPixel



/**
* Set the depth value for a specified pixel.
*/
void FrameBuffer::setDepth(const float x, const float y, const float depth) {

	setDepth((int)(x), (int)(y), depth);

} // end setDepth

/**
* Set the depth value for a specified pixel.
*/
void FrameBuffer::setDepth(const int x, const int y, const float depth) {

	if (checkInWindow(x, y)) {

		depthBuffer[y * window.width + x] = depth;
	}

} // end setDepth

/**
* Returns the depth value for a specified pixel position.
*/
float FrameBuffer::getDepth(const int x, const int y) {

	if (checkInWindow(x, y)) {

		return depthBuffer[y * window.width + x];
	}
	else {
		return 0.0;
	}

} // end getDepth

/**
* Returns the depth value for a specified pixel position.
*/
float FrameBuffer::getDepth(const float x, const float y) {

	return getDepth((int)(x), (int)(y));

} // end getDepth
