#include "Object.h"
#include "Window.h"

OBJObject::OBJObject(const char *filepath) {
	toWorld = glm::mat4(1.0f);
	parse(filepath);

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * normals.size(), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); // Unbind VAO 
}

OBJObject::~OBJObject() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &NBO);
}

void OBJObject::parse(const char *filepath) {
	std::ifstream in(filepath);

	if (!in.is_open()) {
		std::cerr << "Unable to open file." << std::endl;
		exit(EXIT_FAILURE);
	} else {
		char c;
		char *p;
		std::string s;
		const char *sp;

		float min[3] = { std::numeric_limits<float>::max() };
		float max[3] = { std::numeric_limits<float>::min() };

		while ((c = in.peek()) != EOF) {
			if (c == 'v') { // vertex / normal
				in.get();
				bool normal = in.get() == 'n';

				std::getline(in, s);
				sp = s.c_str();

				float t;
				for (int i = 0; i < 3; ++i) {
					t = strtof(sp, &p);
					if (normal) normals.push_back(t);
					else {
						vertices.push_back(t);
						if (t > max[i]) max[i] = t;
						if (t < min[i]) min[i] = t;
					}
					sp = p;
				}
			} else if (c == 'f') { // face
				in.get(); in.get();
				std::getline(in, s);

				unsigned int t;
				for (int i = 0; i < 3; ++i) {
					sp = s.c_str();
					t = strtoul(sp, NULL, 10);
					indices.push_back(t - 1);
					if (i != 2) s = s.substr(s.find(" ") + 1);
				}
			} else {
				std::getline(in, s);
			}
		}

		// Center and Scale Points
		float avg[3] = { (min[0] + max[0]) / 2, (min[1] + max[1]) / 2, (min[2] + max[2]) / 2 };
		float diffX = (max[0] - min[0]) / 2;
		float diffY = (max[1] - min[1]) / 2;
		float diffZ = (max[2] - min[2]) / 2;

		float longestAxis = (diffX > diffY) ? diffX : diffY;
		longestAxis = (longestAxis > diffZ) ? longestAxis : diffZ;
		for (int i = 0; i < vertices.size(); i += 3) {
			vertices[i + 0] -= avg[0];
			vertices[i + 0] /= longestAxis;
			vertices[i + 1] -= avg[1];
			vertices[i + 1] /= longestAxis;
			vertices[i + 2] -= avg[2];
			vertices[i + 2] /= longestAxis;
		}

		in.close();

		if (normals.size() != vertices.size()) std::cerr << "Error reading file: vertices and normals don't match" << std::endl;
	}
}

void OBJObject::draw(GLuint shaderProgram) {
	glm::mat4 MVP = Window::P * Window::V * toWorld;

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "MVP"), 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &toWorld[0][0]);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}