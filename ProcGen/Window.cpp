#include "window.h"

const char* window_title = "Procedural Generation";

GLuint shaderProgram;
GLuint skyboxShader;
Skybox* skybox;

// Default camera parameters
glm::vec3 camPos(0.0f, 0.0f, 20.0f);		
glm::vec3 camLook(0.0f, 0.0f, 0.0f);	
glm::vec3 camUp(0.0f, 1.0f, 0.0f);			

int Window::width;
int Window::height;
 
glm::mat4 Window::P;
glm::mat4 Window::V;

void Window::initialize() {
	skybox = new Skybox();

	shaderProgram = LoadShaders("shaders/shader.vert", "shaders/shader.frag");
	skyboxShader = LoadShaders("shaders/skybox.vert", "shaders/skybox.frag");
}

void Window::cleanUp() {
	delete(skybox);

	glDeleteProgram(shaderProgram);
	glDeleteProgram(skyboxShader);
}

GLFWwindow* Window::createWindow(int width, int height) {
	// Initialize GLFW
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

	if (!window) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Get the width and height of the framebuffer to properly resize the window
	glfwGetFramebufferSize(window, &width, &height);
	// Call the resize callback to make sure things get drawn immediately
	Window::resizeCallback(window, width, height);

	return window;
}

void Window::resizeCallback(GLFWwindow* window, int width, int height) {
	Window::width = width;
	Window::height = height;

	// Set the viewport size
	glViewport(0, 0, width, height);

	if (height > 0) {
		P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
		V = glm::lookAt(camPos, camLook, camUp);
	}
}

void Window::idleCallback() {
	// update here
}

void Window::displayCallback(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgram);

	// draw here
	 
	// draw skybox last
	glUseProgram(skyboxShader);
	skybox->draw(shaderProgram, skyboxShader, V, P);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_ESCAPE) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
}