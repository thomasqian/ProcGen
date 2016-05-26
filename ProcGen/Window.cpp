#include "window.h"

const char* window_title = "Procedural Generation";

static float ROTSCALE = 2.0f;

GLuint shaderProgram;
GLuint skyboxShader;
Skybox* skybox;

// Default camera parameters
glm::vec3 camPos(0.0f, 0.0f, 00.0f);		
glm::vec3 camLook(0.0f, 0.0f, 1.0f);	
glm::vec3 camUp(0.0f, 1.0f, 0.0f);			

int Window::width;
int Window::height;
 
glm::vec3 Window::lastPoint;
glm::vec3 Window::curPoint;
double Window::mouseX;
double Window::mouseY;
double Window::prevMouseX;
double Window::prevMouseY;

bool Window::mouseLeftDown;
bool wDown, aDown, sDown, dDown, qDown, eDown;

glm::mat4 Window::P;
glm::mat4 Window::V;
glm::mat4 I(1.0f);

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

	mouseLeftDown = false;

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
	if (wDown) {
		glm::vec3 direction(glm::normalize(glm::vec3(camLook.x, 0, camLook.z)));
		camPos += direction/50.0f;
	}
	if (aDown) {
		glm::vec3 direction(glm::normalize(glm::vec3(camLook.x, 0, camLook.z)));
		glm::mat4 rotateY(glm::rotate(I, glm::pi<float>() / 2.0f, glm::vec3(0, 1, 0)));
		direction = glm::vec3(rotateY * glm::vec4(direction, 0.0f));
		camPos += direction/50.0f;
	}
	if (sDown) {
		glm::vec3 direction(glm::normalize(glm::vec3(camLook.x, 0, camLook.z)));
		camPos -= direction/50.0f;
	}
	if (dDown) {
		glm::vec3 direction(glm::normalize(glm::vec3(camLook.x, 0, camLook.z)));
		glm::mat4 rotateY(glm::rotate(I, -glm::pi<float>() / 2.0f, glm::vec3(0, 1, 0)));
		direction = glm::vec3(rotateY * glm::vec4(direction, 0.0f));
		camPos += direction/50.0f;
	}
	if (qDown) {
		camPos.y += 0.02f;
	}
	if (eDown) {
		camPos.y -= 0.02f;
	}
	V = glm::lookAt(camPos, camPos + camLook, camUp);
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
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	} else if (key == GLFW_KEY_W) {
		wDown = (action == GLFW_PRESS || action == GLFW_REPEAT);
	} else if (key == GLFW_KEY_A) {
		aDown = (action == GLFW_PRESS || action == GLFW_REPEAT);
	} else if (key == GLFW_KEY_S) {
		sDown = (action == GLFW_PRESS || action == GLFW_REPEAT);
	} else if (key == GLFW_KEY_D) {
		dDown = (action == GLFW_PRESS || action == GLFW_REPEAT);
	} else if (key == GLFW_KEY_Q) {
		qDown = (action == GLFW_PRESS || action == GLFW_REPEAT);
	} else if (key == GLFW_KEY_E) {
		eDown = (action == GLFW_PRESS || action == GLFW_REPEAT);
	}
}

void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if (button == GLFW_MOUSE_BUTTON_LEFT) { // rotation
		if (action == GLFW_PRESS) {
			mouseLeftDown = true;
		} else if (action == GLFW_RELEASE) {
			mouseLeftDown = false;
		}
	}
}

void Window::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
	mouseX = xpos;
	mouseY = ypos;

	if (mouseLeftDown) {
		float dx = mouseX - prevMouseX;
		float dy = mouseY - prevMouseY;

		glm::mat4 rotateLR = glm::rotate(I, -dx * 0.003f, glm::vec3(0, 1, 0));
		glm::vec3 temp = glm::cross(glm::vec3(0, 1, 0), camLook);

		glm::mat4 rotateUD = glm::rotate(I, dy * 0.003f, temp);

		camLook = glm::vec3(rotateUD * rotateLR * glm::vec4(camLook, 0.0f));
	}

	V = glm::lookAt(camPos, camPos + camLook, camUp);
	prevMouseX = mouseX;
	prevMouseY = mouseY;
}