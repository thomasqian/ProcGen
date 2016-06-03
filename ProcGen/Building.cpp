#include "Building.h"
#include "Window.h"

GLfloat Building::baseA[] = {
	-1.0f, 1.0f, 1.0f,
	-1.0f, 0.0f, 1.0f,
	-1.0f, 0.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 0.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 0.0f, -1.0f,
	1.0f, 0.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, 0.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 0.0f, -1.0f,
	1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f,
	-1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 0.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f
};

GLfloat Building::baseB[] = {
	1.0f
};

Building::Building(float x, float y, float z, float scale) {
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
	this->toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z)) * scaleMat;

	for (int i = 0; i < (int)(sizeof(baseA) / sizeof(GLfloat)); ++i) {
		vertices.push_back(baseA[i]);
		if (i % 3 == 0) indices.push_back(i/3);
	}

	// Create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);


	glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
		3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
		GL_FLOAT, // What type these components are
		GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
		3 * sizeof(GLfloat), // Offset between consecutive vertex attributes. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
		(GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Building::~Building() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Building::draw(GLuint shader) {
	glm::mat4 MVP = Window::P * Window::V * toWorld;

	glUseProgram(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "MVP"), 1, GL_FALSE, &MVP[0][0]);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}