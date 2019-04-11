#include "RasterUser.h"

//******** Global Variables ***********

// Frame buffer holding the color values for each pixel
FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

// Some predefined colors.

// Raytracer
RayTracer rayTrace(frameBuffer, BLACK );

// Vector holding all the surfaces in the scene
SurfaceVector surfaces;

// Vector holding all the light sources in the scene
LightVector lights;

// Light sources in the same scene
shared_ptr<LightSource> ambientLight;
shared_ptr<PositionalLight> lightPos;
shared_ptr<DirectionalLight> lightDir;
shared_ptr<SpotLight> spotLight;

//***********************************

/**
* Acts as the display function for the window. 
*/
static void RenderSceneCB()
{
	int frameStartTime = glutGet( GLUT_ELAPSED_TIME ); // Get start time

	// Clear the color buffer
	//frameBuffer.clearColorAndDepthBuffers( ); // Not necessary for ray tracing

	// Ray trace the scene to determine the color of all the pixels in the scene
	rayTrace.raytraceScene( surfaces, lights);

	// Display the color buffer
	frameBuffer.showColorBuffer();

	// Calculate and display time required to render scene.
	int frameEndTime = glutGet( GLUT_ELAPSED_TIME ); // Get end time
	float totalTimeSec = (frameEndTime - frameStartTime) / 1000.0f;

	std::cout << "Render time: " << totalTimeSec << " sec." << std::endl;

} // end RenderSceneCB


// Reset viewport limits for full window rendering each time the window is resized.
// This function is called when the program starts up and each time the window is 
// resized.
static void ResizeCB(int width, int height)
{
	// Size the color buffer to match the window size.
	frameBuffer.setFrameBufferSize( width, height );

	rayTrace.setCameraFrame( dvec3( 0, 0, 0 ), dvec3( 0, 0, -1 ), dvec3( 0, 1, 0 ) );

	rayTrace.calculatePerspectiveViewingParameters( 45.0 );

	// Signal the operating system to re-render the window
	glutPostRedisplay();

} // end ResizeCB


// Responds to 'f' and escape keys. 'f' key allows 
// toggling full screen viewing. Escape key ends the
// program. Allows lights to be individually turned on and off.
static void KeyboardCB(unsigned char key, int x, int y)
{
	switch(key) {

	case('f'): case('F') : // 'f' key to toggle full screen
		glutFullScreenToggle();
		break;
	case(27): // Escape key
		glutLeaveMainLoop();
		break;
	case('0') :
		rayTrace.setRecursionDepth( 0 );
		break;
	case('1') :
		rayTrace.setRecursionDepth( 1 );
		break;
	case('2') :
		rayTrace.setRecursionDepth( 2 );
		break;
	case('3') :
		rayTrace.setRecursionDepth( 3 );
		break;
	case('4') :
		rayTrace.setRecursionDepth( 4 );
		break;
	case('a'):
		ambientLight->enabled = (ambientLight->enabled) ? false : true;
		break;
	case('p'):
		lightPos->enabled = (lightPos->enabled) ? false : true;
		break;
	case('d'):
		lightDir->enabled = (lightDir->enabled) ? false : true;
		break;
	case('s'):
		spotLight->enabled = (spotLight->enabled) ? false : true;
		break;
	case('m'):
		ambientLight->day = true;
		lightPos->day = true;
		lightDir->day = true;
		rayTrace.day = true;
		break;
	case('n'):
		ambientLight->day = false;
		lightPos->day = false;
		lightDir->day = false;
		rayTrace.day = false;
		break;
	case('o'):
		if (rayTrace.renderPerspectiveView == true) {
			rayTrace.renderPerspectiveView = false;
		}
		else {
			rayTrace.renderPerspectiveView = true;
		}
	default:
		std::cout << key << " key pressed." << std::endl;
	}

	glutPostRedisplay();

} // end KeyboardCB


// Responds to presses of the arrow keys
static void SpecialKeysCB(int key, int x, int y)
{
	switch(key) {
	
	case(GLUT_KEY_RIGHT):
		
		break;
	case(GLUT_KEY_LEFT):
		
		break;
	default:
		std::cout << key << " key pressed." << std::endl;
	}

	glutPostRedisplay();

} // end SpecialKeysCB


void buildScene()
{
	// Initialize random seed - used to create random colors
	srand((unsigned int)time(NULL));
	Material redMat(RED);
	redMat.emissive = 0.3 * RED;

	std::vector<dvec3> planeVec;
	planeVec.push_back(dvec3(10.0, 10.0, -18.0));
	planeVec.push_back(dvec3(10.0, 10.0, -19.0));
	planeVec.push_back(dvec3(0.0, 10.0, -18.0));

	std::vector<dvec3> planeVec2;
	planeVec2.push_back(dvec3(-10.0, -10.0, -18.0));
	planeVec2.push_back(dvec3(-10.0, -10.0, -19.0));
	planeVec2.push_back(dvec3(0.0, -10.0, -18.0));

	std::vector<dvec3> polyVec;
	polyVec.push_back(dvec3(-3.5, 2.0, -10.0));
	polyVec.push_back(dvec3(-4.0, 0.0, -10.0));
	polyVec.push_back(dvec3(-3.0, 0.0, -10.0));

	shared_ptr<Sphere> redBall = make_shared<Sphere>(dvec3(0.0, -1.0, -4.0 ), 0.7, redMat);
	shared_ptr<Sphere> blueBall = make_shared<Sphere>(dvec3(1.0, 0.0, -3.0), 0.4, BLUE);
	shared_ptr<Sphere> grayBall = make_shared<Sphere>(dvec3(1.0, 0.5, -7.0), 1.5, DARK_GRAY);
	shared_ptr<Plane> plane = make_shared<Plane>(dvec3(0,-3, 0), dvec3(0,1,0), MAGENTA * 0.5);
//	shared_ptr<Plane> bluePlane = make_shared<Plane>(planeVec2, YELLOW);
	shared_ptr<ConvexPolygon> magentaPolygon = make_shared<ConvexPolygon>(polyVec, RED);
	shared_ptr<Ellipsoid> cyanEllipse = make_shared<Ellipsoid>(dvec3(-2.0, -2.0, -6.0), CYAN);
	shared_ptr<Cylinder> greenCylinder = make_shared<Cylinder>(dvec3(3.3, 2.0, -9.0), GREEN);

	//surfaces.push_back(redBall);
	surfaces.push_back(blueBall);
	surfaces.push_back(grayBall);
	surfaces.push_back(magentaPolygon);
	surfaces.push_back(cyanEllipse);
	surfaces.push_back(plane);
//	surfaces.push_back(bluePlane);
	surfaces.push_back(greenCylinder);

	ambientLight = make_shared<LightSource>(WHITE);
	ambientLight->ambientLightColor = color(0.15, 0.15, 0.15, 1.0);
	lightPos = make_shared<PositionalLight>(dvec3(-10.0, 10.0, 10.0), color(1.0, 1.0, 1.0, 1));
	lightDir = make_shared<DirectionalLight>(dvec3(1, 1, 1), color(0.75, 0.75, 0.75, 1));
	spotLight = make_shared<SpotLight>(dvec3(0, 0, 0), dvec3(0, 0, -10.0), glm::cos(glm::radians(15.0f)), color(1.0, 1.0, 1.0, 1));

	lights.push_back(lightPos);
	lights.push_back(lightDir);
	lights.push_back(ambientLight);
	lights.push_back(spotLight);
}


// Register as the "idle" function to have the screen continously
// repainted. Due to software rendering, the frame rate will not
// be fast enough to support motion simulation
static void animate()  
{
	glutPostRedisplay();

} // end animate


int main(int argc, char** argv)
{
	// freeGlut and Window initialization ***********************

    // Pass any applicable command line arguments to GLUT. These arguments
	// are platform dependent.
    glutInit(&argc, argv);

	// Set the initial display mode.
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA );

	// Set the initial window size
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Create a window using a string and make it the current window.
	GLuint world_Window = glutCreateWindow("Ray Trace");

	// Indicate to GLUT that the flow of control should return to the program after
	// the window is closed and the GLUTmain loop is exited.
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// Request that the window be made full screen
	//glutFullScreenToggle();

	// Set red, green, blue, and alpha to which the color buffer is cleared.
	frameBuffer.setClearColor(color(0,0,0,1));

	// Set the color to which pixels will be cleared if there is no intersection.
	// TODO
	rayTrace.setDefaultColor(BLACK);

	// Callback for window redisplay
	glutDisplayFunc(RenderSceneCB);		
	glutReshapeFunc(ResizeCB);
	glutKeyboardFunc(KeyboardCB);
	glutSpecialFunc(SpecialKeysCB);
	//glutIdleFunc( RenderSceneCB );

	// Create the objects and light sources.
	buildScene();

	// Enter the GLUT main loop. Control will not return until the window is closed.
    glutMainLoop();

	// To keep the console open on shutdown, start the project with Ctrl+F5 instead of just F5.

	return 0;

} // end main