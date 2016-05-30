#pragma once

#include "Window.h"
#include <random>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

// 2^n + 1
#define EL 257

const static unsigned int seed = 5;
const static float scale = 50.0f;

class Terrain {
private:
	float hm[EL][EL];
	bool set[EL][EL];
	int offset;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	GLuint VAO, VBO, EBO;

public:
	Terrain();
	~Terrain();

	void generate();
	bool inBounds(int, int);

	void draw(GLuint);

	void generateDiamond(int, int, int);
	void generateSquare(int, int, int);
};

