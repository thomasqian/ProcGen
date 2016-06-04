#include "window.h"

const char* window_title = "Procedural Generation";

static const float ROTSCALE = 0.003f;
static const float MOVESPEED = 0.7f;

GLuint shaderProgram;
GLuint skyboxShader;
GLuint buildingShader;
Skybox* skybox;

// Default camera parameters
glm::vec3 camPos(0.0f, 200.0f, 00.0f);		
glm::vec3 camLook(1.0f, 0.0f, 1.0f);	
glm::vec3 camUp(0.0f, 1.0f, 0.0f);			

int Window::width;
int Window::height;
 
double Window::mouseX;
double Window::mouseY;
double Window::prevMouseX;
double Window::prevMouseY;

bool Window::mouseLeftDown;
bool Window::mouseMidDown;
bool wDown, aDown, sDown, dDown, qDown, eDown;

glm::mat4 Window::P;
glm::mat4 Window::V;
glm::mat4 I(1.0f);
glm::vec3 UP(0, 1, 0);
glm::mat4 rotateY90(glm::rotate(I, glm::pi<float>() / 2.0f, UP));

Terrain* t;
Texture* grass;
Texture* sand;
Texture* snow;
Texture* logs;
Texture* shingles;

void Window::initialize() {
	skybox = new Skybox();
	t = new Terrain();

	grass = new Texture("textures/grass.ppm");
	sand = new Texture("textures/sand.ppm");
	snow = new Texture("textures/snow.ppm");
	logs = new Texture("textures/wood.ppm");
	shingles = new Texture("textures/shingles.ppm");

	shaderProgram = LoadShaders("shaders/shader.vert", "shaders/shader.frag");
	skyboxShader = LoadShaders("shaders/skybox.vert", "shaders/skybox.frag");
	buildingShader = LoadShaders("shaders/buildings.vert", "shaders/buildings.frag");

	fprintf(stderr, "back in window\n");
}

void Window::cleanUp() {
	delete(skybox);
	delete(t);

	delete(grass);
	delete(sand);
	delete(snow);

	glDeleteProgram(shaderProgram);
	glDeleteProgram(skyboxShader);
	glDeleteProgram(buildingShader);
}

GLFWwindow* Window::createWindow(int width, int height) {
	// Initialize GLFW
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	mouseLeftDown = false;

	// 4x antialiasing
	//glfwWindowHint(GLFW_SAMPLES, 4);

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
		V = glm::lookAt(camPos, camPos + camLook, camUp);
	}
}

void Window::idleCallback() {
	if (wDown) {
		glm::vec3 direction(glm::normalize(glm::vec3(camLook.x, 0, camLook.z)));
		camPos += direction * MOVESPEED;
	}
	if (aDown) {
		glm::vec3 direction(glm::normalize(glm::vec3(camLook.x, 0, camLook.z)));
		direction = glm::vec3(rotateY90 * glm::vec4(direction, 0.0f));
		camPos += direction * MOVESPEED;
	}
	if (sDown) {
		glm::vec3 direction(glm::normalize(glm::vec3(camLook.x, 0, camLook.z)));
		camPos -= direction * MOVESPEED;
	}
	if (dDown) {
		glm::vec3 direction(glm::normalize(glm::vec3(camLook.x, 0, camLook.z)));
		direction = glm::vec3(rotateY90 * glm::vec4(direction, 0.0f));
		camPos -= direction * MOVESPEED;
	}
	if (qDown) {
		camPos.y -= MOVESPEED;
	}
	if (eDown) {
		camPos.y += MOVESPEED;
	}
	V = glm::lookAt(camPos, camPos + camLook, camUp);
}

void Window::displayCallback(GLFWwindow* window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glCullFace(GL_BACK);
	glUseProgram(skyboxShader);
	skybox->draw(shaderProgram, skyboxShader, V, P);

	glCullFace(GL_BACK);
	glUseProgram(shaderProgram);

	glUniform1i(glGetUniformLocation(shaderProgram, "sand"), 1);
	glUniform1i(glGetUniformLocation(shaderProgram, "grass"), 2);
	glUniform1i(glGetUniformLocation(shaderProgram, "snow"), 3);

	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, sand->textureID);

	glActiveTexture(GL_TEXTURE0 + 2);
	glBindTexture(GL_TEXTURE_2D, grass->textureID);

	glActiveTexture(GL_TEXTURE0 + 3);
	glBindTexture(GL_TEXTURE_2D, snow->textureID);

	t->draw(shaderProgram, buildingShader, logs, shingles);

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
	} else if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		delete(t);
		t = new Terrain();
	}
	else if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		t->toggle();
	}
	else if(key == GLFW_KEY_TAB && action == GLFW_PRESS){
		mouseMidDown = !mouseMidDown;
		if(mouseMidDown){
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
 }

void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT) { // rotation
		if (action == GLFW_PRESS) {
			mouseLeftDown = true;
		} else if (action == GLFW_RELEASE) {
			mouseLeftDown = false;
		}
	}
	else if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS){
		mouseMidDown = !mouseMidDown;
		if(mouseMidDown){
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
}

void Window::cursorPosCallback(GLFWwindow* window, double xpos, double ypos){
	mouseX = xpos;
	mouseY = ypos;
	if(mouseMidDown){
		float dx = xpos - (float)Window::width/2;
		float dy = ypos - (float)Window::height/2;
		glm::mat4 rotateLR = glm::rotate(I, -dx * ROTSCALE, UP);
		glm::vec3 xaxis = glm::cross(UP, camLook);
		glm::mat4 rotateUD = glm::rotate(I, dy * ROTSCALE, xaxis);
		camLook = glm::vec3(rotateUD * rotateLR * glm::vec4(camLook, 0.0f));
		glfwSetCursorPos(window, (double)Window::width/2, (double)Window::height/2);
	}
	else if (mouseLeftDown) {
		float dx = mouseX - prevMouseX;
		float dy = mouseY - prevMouseY;
		glm::mat4 rotateLR = glm::rotate(I, -dx * ROTSCALE, UP);
		glm::vec3 xaxis = glm::cross(UP, camLook);
		glm::mat4 rotateUD = glm::rotate(I, dy * ROTSCALE, xaxis);
		camLook = glm::vec3(rotateUD * rotateLR * glm::vec4(camLook, 0.0f));
	}
	prevMouseX = mouseX;
	prevMouseY = mouseY;
}

void Window::scrollCallback(GLFWwindow* window, double sx, double sy) {
	camPos = camPos + camLook*(float)sy*10.0f;
}