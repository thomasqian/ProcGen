#pragma once

#include <random>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <vector>

const static float baseHeight = 10.0f;

class Building {
public:
	Building(float, float, float, float);
	~Building();

	void draw(GLuint);

private:
	glm::mat4 toWorld;
	GLuint VBO, VAO, EBO;

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	static GLfloat baseA[];
		static GLfloat midA[];
			static GLfloat topA[];
			static GLfloat topB[];
		static GLfloat midB[];
			static GLfloat topC[];
			static GLfloat topD[];

	static GLfloat baseB[];
		static GLfloat midC[];
};

