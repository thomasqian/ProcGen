#pragma once

#include "Texture.h"

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

	static void initTextures();
	static void freeTextures();
	void draw(GLuint, float, float);

private:
	glm::mat4 toWorld;
	glm::mat4 toWorldUnscaled;
	GLuint VBO, VAO, NBO, EBO;

	float x, y, z;

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	std::vector<glm::vec3> normals;

	static GLfloat baseA[];
		static GLfloat midA[];
			static GLfloat topA[];
			static GLfloat topB[];
		static GLfloat midB[];
			static GLfloat topC[];
			static GLfloat topD[];

	static GLfloat baseB[];
		static GLfloat midC[];
		static GLfloat midD[];
			static GLfloat topE[];
			static GLfloat topF[];

	static Texture* wood;
	static Texture* shingles;
	static Texture* snowwall;
	static Texture* snowroof;
	static Texture* sandbrick;
	static Texture* strawroof;
};

