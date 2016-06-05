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

GLfloat Building::midD[] = {
	-1.0f, 2.0f, 1.0f, //A
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 0.0f,
	-1.0f, 2.0f, 1.0f,
	-1.0f, 1.0f, 0.0f,
	-1.0f, 2.0f, 0.0f,

	-1.0f, 2.0f, 0.0f, //B
	-1.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	-1.0f, 2.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 2.0f, 0.0f,

	0.0f, 2.0f, 0.0f, //C
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, -1.0f,

	0.0f, 2.0f, 0.0f, //D
	0.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	0.0f, 2.0f, 0.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 2.0f, 0.0f,

	1.0f, 2.0f, 0.0f, //E
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 2.0f, 0.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 2.0f, 1.0f,

	1.0f, 2.0f, 1.0f, //F
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 2.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 2.0f, 1.0f,

	1.0f, 2.0f, 1.0f, //G
	-1.0f, 2.0f, 1.0f,
	-1.0f, 2.0f, 0.0f,
	1.0f, 2.0f, 1.0f,
	-1.0f, 2.0f, 0.0f,
	1.0f, 2.0f, 0.0f,
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

GLfloat Building::topE[] = {
	0.0f, 2.5f, 0.5f, //A
	-1.0f, 2.0f, 0.0f,
	1.0f, 2.0f, 0.0f,
	0.0f, 2.5f, 0.5f, //B
	1.0f, 2.0f, 0.0f,
	1.0f, 2.0f, 1.0f,
	0.0f, 2.5f, 0.5f, //C
	1.0f, 2.0f, 1.0f,
	-1.0f, 2.0f, 1.0f,
	0.0f, 2.5f, 0.5f, //D
	-1.0f, 2.0f, 1.0f,
	-1.0f, 2.0f, 0.0f
};

GLfloat Building::topF[] = {
	-1.0f, 2.5f, 0.5f, //A
	-1.0f, 2.0f, 0.0f,
	1.0f, 2.0f, 0.0f,
	-1.0f, 2.5f, 0.5f,
	1.0f, 2.0f, 0.0f,
	1.0f, 2.5f, 0.5f,
	1.0f, 2.5f, 0.5f, //B
	1.0f, 2.0f, 0.0f,
	1.0f, 2.0f, 1.0f,
	1.0f, 2.5f, 0.5f, //C
	1.0f, 2.0f, 1.0f,
	-1.0f, 2.0f, 1.0f,
	1.0f, 2.5f, 0.5f,
	-1.0f, 2.0f, 1.0f,
	-1.0f, 2.5f, 0.5f,
	-1.0f, 2.5f, 0.5f, //D
	-1.0f, 2.0f, 1.0f,
	-1.0f, 2.0f, 0.0f
};

Texture* Building::wood;
Texture* Building::shingles;
Texture* Building::snowwall;
Texture* Building::snowroof;
Texture* Building::sandbrick;
Texture* Building::strawroof;

void Building::initTextures() {
	wood = new Texture("textures/wood.ppm");
	shingles = new Texture("textures/shingles.ppm");
	snowwall = new Texture("textures/snowwall.ppm");
	snowroof = new Texture("textures/snowroof.ppm");
	sandbrick = new Texture("textures/sandbrick.ppm");
	strawroof = new Texture("textures/strawroof.ppm");
}

Building::Building(float x, float y, float z, float scale) : x(x), y(y), z(z) {
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
	glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0f), ((float)(rngB()%4)*glm::pi<float>())/2.0f, glm::vec3(0, 1, 0));
	this->toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z)) * scaleMat * rotateMat;
	this->toWorldUnscaled = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z)) * rotateMat;

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
			for (int i = 0; i < (int)(sizeof(midD)/sizeof(GLfloat)); ++i) {
				vertices.push_back(midD[i]);
			}
			if(rngB()%2 == 0){
				for (int i = 0; i < (int)(sizeof(topE)/sizeof(GLfloat)); ++i) {
					vertices.push_back(topE[i]);
				}
			}
			else{
				for (int i = 0; i < (int)(sizeof(topF)/sizeof(GLfloat)); ++i) {
					vertices.push_back(topF[i]);
				}
			}
		}
	}
	
	for(int i = 0; i < vertices.size(); i++){
		indices.push_back(i);
	}
	
	for(int i = 0; i < vertices.size(); i++){
		if(i % 9 == 0){
			glm::vec3 pointA = glm::vec3(vertices[i + 0], vertices[i + 1], vertices[i + 2]);
			glm::vec3 pointB = glm::vec3(vertices[i + 3], vertices[i + 4], vertices[i + 5]);
			glm::vec3 pointC = glm::vec3(vertices[i + 6], vertices[i + 7], vertices[i + 8]);
			glm::vec3 norm = glm::normalize(glm::cross(pointB - pointA, pointC - pointA));
			normals.push_back(norm);
			normals.push_back(norm);
			normals.push_back(norm);
		}
	}
	//fprintf(stderr, "n: %.2f, %.2f, %.2f\n", normals[normals.size()-1].x, normals[normals.size()-1].y, normals[normals.size()-1].z);

	// Create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &NBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Building::~Building() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &NBO);
}

void Building::freeTextures() {
	delete(wood);
	delete(shingles);
	delete(snowwall);
	delete(snowroof);
	delete(sandbrick);
	delete(strawroof);
}

void Building::draw(GLuint shader, float min, float max) {
	glm::mat4 MVP = Window::P * Window::V * toWorld;

	glUseProgram(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "MVP"), 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &toWorld[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader, "modelUnscaled"), 1, GL_FALSE, &toWorldUnscaled[0][0]);

	glUniform1f(glGetUniformLocation(shader, "min"), min);
	glUniform1f(glGetUniformLocation(shader, "max"), max);
	glUniform1f(glGetUniformLocation(shader, "ypos"), y);

	glUniform1i(glGetUniformLocation(shader, "wood"), 0);
	glUniform1i(glGetUniformLocation(shader, "shingles"), 1);
	glUniform1i(glGetUniformLocation(shader, "snowwall"), 2);
	glUniform1i(glGetUniformLocation(shader, "snowroof"), 3);
	glUniform1i(glGetUniformLocation(shader, "sandbrick"), 4);
	glUniform1i(glGetUniformLocation(shader, "strawroof"), 5);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, wood->textureID);
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, shingles->textureID);
	glActiveTexture(GL_TEXTURE0 + 2);
	glBindTexture(GL_TEXTURE_2D, snowwall->textureID);
	glActiveTexture(GL_TEXTURE0 + 3);
	glBindTexture(GL_TEXTURE_2D, snowroof->textureID);
	glActiveTexture(GL_TEXTURE0 + 4);
	glBindTexture(GL_TEXTURE_2D, sandbrick->textureID);
	glActiveTexture(GL_TEXTURE0 + 5);
	glBindTexture(GL_TEXTURE_2D, strawroof->textureID);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}