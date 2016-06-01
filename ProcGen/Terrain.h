#pragma once

#include "Window.h"

#include <random>
#include <iostream>
#include <vector>
#include <ctime>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

// 2^n + 1
//#define EL 65

const static int EL = 129;
//const static unsigned int seed = 123;
const static float scale = 5.0f;
const static float initialOffset = 150.0f;

class Terrain {
private:
	float hm[EL][EL];
	bool set[EL][EL];

	int style;
	float min, max;

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	GLuint VAO, VBO, EBO;

public:
	Terrain();
	~Terrain();

	void generate();
	bool inBounds(int, int);

	void draw(GLuint);

	void generateDiamond(int, int, int, float);
	void generateSquare(int, int, int, float);

	void toggle();
};

