#pragma once

#include "shader.h"
#include "Skybox.h"
#include "Terrain.h"
#include "Texture.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Window {
public:
	static float time;
	static int width;
	static int height;
	static glm::mat4 P;
	static glm::mat4 V;
	static void initialize();
	static void cleanUp();
	static GLFWwindow* createWindow(int width, int height);
	static void resizeCallback(GLFWwindow* window, int width, int height);
	static void idleCallback();
	static void displayCallback(GLFWwindow*);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void scrollCallback(GLFWwindow* window, double sx, double sy);

private:
	static double prevMouseX, prevMouseY, mouseX, mouseY;
	static bool mouseLeftDown, mouseMidDown;
};