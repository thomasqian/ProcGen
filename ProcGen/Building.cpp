#include "Building.h"
#include "Window.h"

std::mt19937_64 rngB(time(NULL));

GLfloat Building::baseA[] = {
	-1.0f, 1.0f, 1.0f, //A
	-1.0f, 0.0f, 1.0f,
	-1.0f, 0.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 0.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f, //B
	-1.0f, 0.0f, -1.0f,
	1.0f, 0.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, 0.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f, //C
	1.0f, 0.0f, -1.0f,
	1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, //D
	1.0f, 0.0f, 1.0f,
	-1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 0.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, //E
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f
};

GLfloat Building::baseB[] = {
	-1.0f, 1.0f, 1.0f, //A
	-1.0f, 0.0f, 1.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f, //B
	-1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f, //C
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 1.0f, -1.0f,
	0.0f, 1.0f, -1.0f, //D
	0.0f, 0.0f, -1.0f,
	1.0f, 0.0f, -1.0f,
	0.0f, 1.0f, -1.0f,
	1.0f, 0.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f, //E
	1.0f, 0.0f, -1.0f,
	1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, //F
	1.0f, 0.0f, 1.0f,
	-1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 0.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, //G
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
};

GLfloat Building::midA[] = {
	-0.5f, 2.0f, -0.5f, //A
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-0.5f, 2.0f, -0.5f,
	1.0f, 1.0f, -1.0f,
	0.5f, 2.0f, -0.5f,
	0.5f, 2.0f, -0.5f, //B
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	0.5f, 2.0f, -0.5f,
	1.0f, 1.0f, 1.0f,
	0.5f, 2.0f, 0.5f,
	0.5f, 2.0f, 0.5f, //C
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	0.5f, 2.0f, 0.5f,
	-1.0f, 1.0f, 1.0f,
	-0.5f, 2.0f, 0.5f,
	-0.5f, 2.0f, 0.5f, //D
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	-0.5f, 2.0f, 0.5f,
	-1.0f, 1.0f, -1.0f,
	-0.5f, 2.0f, -0.5f,
	-0.5f, 2.0f, 0.5f, //E
	-0.5f, 2.0f, -0.5f,
	0.5f, 2.0f, -0.5f,
	-0.5f, 2.0f, 0.5f,
	0.5f, 2.0f, -0.5f,
	0.5f, 2.0f, 0.5f
};

GLfloat Building::midB[] = {
	-0.5f, 2.0f, -1.0f, //A
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-0.5f, 2.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	0.5f, 2.0f, -1.0f,
	0.5f, 2.0f, -1.0f, //B
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	0.5f, 2.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	0.5f, 2.0f, 1.0f,
	0.5f, 2.0f, 1.0f, //C
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	0.5f, 2.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-0.5f, 2.0f, 1.0f,
	-0.5f, 2.0f, 1.0f, //D
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	-0.5f, 2.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	-0.5f, 2.0f, -1.0f,
	-0.5f, 2.0f, 1.0f, //E
	-0.5f, 2.0f, -1.0f,
	0.5f, 2.0f, -1.0f,
	-0.5f, 2.0f, 1.0f,
	0.5f, 2.0f, -1.0f,
	0.5f, 2.0f, 1.0f
};

GLfloat Building::midC[] = {
	-0.5f, 1.5f, 0.5f, //A
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 0.0f,
	-0.5f, 1.5f, 0.5f, //B
	-1.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	-0.5f, 1.5f, 0.5f,
	0.0f, 1.0f, 0.0f,
	0.5f, 1.5f, 0.5f,
	0.5f, 1.5f, 0.5f, //C
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, -1.0f,
	0.5f, 1.5f, 0.5f,
	0.0f, 1.0f, -1.0f,
	0.5f, 1.5f, -0.5f,
	0.5f, 1.5f, -0.5f, //D
	0.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	0.5f, 1.5f, -0.5f, //E
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	0.5f, 1.5f, -0.5f,
	1.0f, 1.0f, 1.0f,
	0.5f, 1.5f, 0.5f,
	0.5f, 1.5f, 0.5f, //F
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	0.5f, 1.5f, 0.5f,
	-1.0f, 1.0f, 1.0f,
	-0.5f, 1.5f, 0.5f,
};

GLfloat Building::topA[] = {
	0.0f, 2.5f, 0.0f, //A
	-0.5f, 2.0f, -0.5f,
	0.5f, 2.0f, -0.5f,
	0.0f, 2.5f, 0.0f, //B
	0.5f, 2.0f, -0.5f,
	0.5f, 2.0f, 0.5f,
	0.0f, 2.5f, 0.0f, //C
	0.5f, 2.0f, 0.5f,
	-0.5f, 2.0f, 0.5f,
	0.0f, 2.5f, 0.0f, //D
	-0.5f, 2.0f, 0.5f,
	-0.5f, 2.0f, -0.5f,
};

GLfloat Building::topB[] = {
	0.0f, 2.5f, -0.5f, //A
	-0.5f, 2.0f, -0.5f,
	0.5f, 2.0f, -0.5f,
	0.0f, 2.5f, -0.5f, //B
	0.5f, 2.0f, -0.5f,
	0.5f, 2.0f, 0.5f,
	0.0f, 2.5f, -0.5f,
	0.5f, 2.0f, 0.5f,
	0.0f, 2.5f, 0.5f,
	0.0f, 2.5f, 0.5f, //C
	0.5f, 2.0f, 0.5f,
	-0.5f, 2.0f, 0.5f,
	0.0f, 2.5f, 0.5f, //D
	-0.5f, 2.0f, 0.5f,
	-0.5f, 2.0f, -0.5f,
	0.0f, 2.5f, 0.5f,
	-0.5f, 2.0f, -0.5f,
	0.0f, 2.5f, -0.5f,
};

GLfloat Building::topC[] = {
	0.0f, 2.5f, 0.0f, //A
	-0.5f, 2.0f, -1.0f,
	0.5f, 2.0f, -1.0f,
	0.0f, 2.5f, 0.0f, //B
	0.5f, 2.0f, -1.0f,
	0.5f, 2.0f, 1.0f,
	0.0f, 2.5f, 0.0f, //C
	0.5f, 2.0f, 1.0f,
	-0.5f, 2.0f, 1.0f,
	0.0f, 2.5f, 0.0f, //D
	-0.5f, 2.0f, 1.0f,
	-0.5f, 2.0f, -1.0f,
};

GLfloat Building::topD[] = {
	0.0f, 2.5f, -1.0f, //A
	-0.5f, 2.0f, -1.0f,
	0.5f, 2.0f, -1.0f,
	0.0f, 2.5f, -1.0f, //B
	0.5f, 2.0f, -1.0f,
	0.5f, 2.0f, 1.0f,
	0.0f, 2.5f, -1.0f,
	0.5f, 2.0f, 1.0f,
	0.0f, 2.5f, 1.0f,
	0.0f, 2.5f, 1.0f, //C
	0.5f, 2.0f, 1.0f,
	-0.5f, 2.0f, 1.0f,
	0.0f, 2.5f, 1.0f, //D
	-0.5f, 2.0f, 1.0f,
	-0.5f, 2.0f, -1.0f,
	0.0f, 2.5f, 1.0f,
	-0.5f, 2.0f, -1.0f,
	0.0f, 2.5f, -1.0f,
};

Building::Building(float x, float y, float z, float scale) {
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
	this->toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z)) * scaleMat;

	if(rngB()%2 == 0){
		for (int i = 0; i < (int)(sizeof(baseA)/sizeof(GLfloat)); ++i) {
			vertices.push_back(baseA[i]);
		}
		if(rngB()%2 == 0){
			for (int i = 0; i < (int)(sizeof(midA)/sizeof(GLfloat)); ++i) {
				vertices.push_back(midA[i]);
			}
			if(rngB()%2 == 0){
				for (int i = 0; i < (int)(sizeof(topA)/sizeof(GLfloat)); ++i) {
					vertices.push_back(topA[i]);
				}
			}
			else{
				for (int i = 0; i < (int)(sizeof(topB)/sizeof(GLfloat)); ++i) {
					vertices.push_back(topB[i]);
				}
			}
		}
		else{
			for (int i = 0; i < (int)(sizeof(midB)/sizeof(GLfloat)); ++i) {
				vertices.push_back(midB[i]);
			}
			if(rngB()%2 == 0){
				for (int i = 0; i < (int)(sizeof(topC)/sizeof(GLfloat)); ++i) {
					vertices.push_back(topC[i]);
				}
			}
			else{
				for (int i = 0; i < (int)(sizeof(topD)/sizeof(GLfloat)); ++i) {
					vertices.push_back(topD[i]);
				}
			}
		}
	}
	else{
		for (int i = 0; i < (int)(sizeof(baseB)/sizeof(GLfloat)); ++i) {
			vertices.push_back(baseB[i]);
		}
		if(rngB()%2 == 0){
			for (int i = 0; i < (int)(sizeof(midC)/sizeof(GLfloat)); ++i) {
				vertices.push_back(midC[i]);
			}
		}
		else{
		}
	}
	
	

	for(int i = 0; i < vertices.size(); i++){
		indices.push_back(i);
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