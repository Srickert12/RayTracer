#pragma once

#include <iostream> // Stream input and output operations
#include <vector> // Sequence containers for arrays that can change in size
#include <memory> // General utilities to manage dynamic memory

// Glut takes care of all the system-specific chores required for creating windows, 
// initializing OpenGL contexts, and handling input events
#include <GL/freeglut.h>

// Initialize matrices to Identity and vectors to zero vector
#define GLM_FORCE_CTOR_INIT

// Forward declaration to speed compilation
#include "glm/fwd.hpp"

// Basic GLM functionality
#include "glm/glm.hpp"

// Stable glm extensions
// https://glm.g-truc.net/0.9.9/api/a01364.html
#include <glm/gtc/matrix_transform.hpp>
// https://glm.g-truc.net/0.9.9/api/a00437.html
#include <glm/gtc/type_ptr.hpp>
// https://glm.g-truc.net/0.9.9/api/a00395.html
#include <glm/gtc/constants.hpp>
// https://glm.g-truc.net/0.9.9/api/a01370.html
#include <glm/gtc/quaternion.hpp>

// Allows experimental extensions of glm to be used
#define GLM_ENABLE_EXPERIMENTAL

// For simple scale, rotate, and translate functions
// https://glm.g-truc.net/0.9.9/api/a00596.html
#include <glm/gtx/transform.hpp>
// For additional quaterion functionality
// https://glm.g-truc.net/0.9.9/api/a01373.html
#include <glm/gtx/quaternion.hpp> 
// https://glm.g-truc.net/0.9.9/api/a00736.html#gae6aa26ccb020d281b449619e419a609e
#include <glm/gtx/euler_angles.hpp>

// #defines for text substitution in source code prior to compile

// Attenuation factors
const double CONSTANT_ATTEN = 1.0;
const double LINEAR_ATTEN = 0.01;
const double QUADRATIC_ATTEN = 0.001;

const int WINDOW_WIDTH = 512; // Default window width in pixels
const int WINDOW_HEIGHT = 316; // Default window height in pixels = width/1.618

// Small value used to create offset to avoid "surface acne"
const double EPSILON = 1.0E-4;

// Define pi as type double.
const double M_PI = glm::pi<double>( );

// Allow reference to vec4 as a "color"
typedef glm::dvec4 color;

const color BLACK = color( 0.0, 0.0, 0.0, 1.0 );
const color NO_COLOR = color(0.0, 0.0, 0.0, 0.0);
const color RED = color( 1.0, 0.0, 0.0, 1.0 );
const color GREEN = color( 0.0, 1.0, 0.0, 1.0 );
const color BLUE = color( 0.0, 0.0, 1.0, 1.0 );
const color MAGENTA = color( 1.0, 0.0, 1.0, 1.0 );
const color YELLOW = color( 1.0, 1.0, 0.0, 1.0 );
const color CYAN = color( 0.0, 1.0, 1.0, 1.0 );
const color WHITE = color( 1.0, 1.0, 1.0, 1.0 );
const color GRAY = color( 0.5, 0.5, 0.5, 1.0 );
const color LIGHT_GRAY = color( 0.8, 0.8, 0.8, 1.0 );
const color DARK_GRAY = color( 0.3, 0.3, 0.3, 1.0 );
const color LIGHT_BLUE = color(0.53, 0.81, 1.0, 1.0);

// defines to clean up syntax associated with Surface and Light vertors of shared smart pointers
typedef std::vector<std::shared_ptr<class Surface>>  SurfaceVector;
typedef std::vector<std::shared_ptr<struct LightSource>> LightVector;

// Using statements to make identifiers from another namespace available without qualification
using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::shared_ptr;
using std::make_shared;

using glm::dvec2;
using glm::dvec3;
using glm::dvec4;
using glm::dmat2;
using glm::dmat3;
using glm::dmat4;

// Function for generating random colors. Alpha value is always 
// set to 1.0
color getRandomColor();

// Simple streaming for vectors and matrices.
ostream &operator << ( ostream &os, const dvec2 &v );
ostream &operator << ( ostream &os, const dvec3 &v );
ostream &operator << ( ostream &os, const dvec4 &v );
ostream &operator << ( ostream &os, const dmat2 &v );
ostream &operator << ( ostream &os, const dmat3 &v );
ostream &operator << ( ostream &os, const dmat4 &v );

template <class T>
ostream &operator << ( ostream &os, const std::vector<T> &V )
{
	os << "[" << endl;
	for( size_t i = 0; i < V.size( ); i++ ) {
		os << '\t' << V[i] << endl;
	}
	os << "]" << endl;
	return os;
}

