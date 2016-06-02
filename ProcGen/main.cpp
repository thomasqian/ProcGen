#include "main.h"

GLFWwindow* window;

void errorCallback(int error, const char* description) {
	fputs(description, stderr);
}

void setupCallbacks() {
	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(window, Window::keyCallback);
	glfwSetFramebufferSizeCallback(window, Window::resizeCallback);
	glfwSetMouseButtonCallback(window, Window::mouseButtonCallback);
	glfwSetCursorPosCallback(window, Window::cursorPosCallback);
	glfwSetScrollCallback(window, Window::scrollCallback);
}

void setupGLEW() {
	// Initialize GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		glfwTerminate();
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}

void setupOpenGLSettings() {
	setupGLEW();
	// Enable depth buffering
	glEnable(GL_DEPTH_TEST);
	// Related to shaders and z value comparisons for the depth buffer
	glDepthFunc(GL_LEQUAL);
	// Set polygon drawing mode to fill front and back of each polygon
	// You can also use the paramter of GL_LINE instead of GL_FILL to see wireframes
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void printVersions() {
	// Get info of GPU and supported OpenGL version
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

	//If the shading language symbol is defined
#ifdef GL_SHADING_LANGUAGE_VERSION
	std::printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif
}

int main(void) {
	window = Window::createWindow(1920, 1440);//(800, 600);
	printVersions();
	setupCallbacks();
	setupOpenGLSettings();
	Window::initialize();

	while (!glfwWindowShouldClose(window)) {
		Window::displayCallback(window);
		Window::idleCallback();
	}

	Window::cleanUp();
	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}