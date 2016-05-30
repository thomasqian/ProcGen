#include "Terrain.h"

std::mt19937 rng(seed);
glm::mat4 toWorld(1.0f);

Terrain::Terrain() {
	
	//std::uniform_int_distribution<int> gen(min, max); // uniform, unbiased

	for (int x = 0; x < EL; ++x) {
		for (int z = 0; z < EL; ++z) {
			set[x][z] = false;
		}
	}

	offset = 10;

	hm[0][0] = rng() % 10;
	hm[0][EL] = rng() % 10;
	hm[EL][0] = rng() % 10;
	hm[EL][EL] = rng() % 10;

	set[0][0] = true;
	set[0][EL] = true;
	set[EL][0] = true;
	set[EL][EL] = true;

	generate();
	
	/*for (int z = 0; z < EL; z++) {
		for (int x = 0; x < EL; x++) {
			fprintf(stderr, "%.2f ", hm[x][z]);
		}
		fprintf(stderr, "\n");
	}
	for (int z = 0; z < EL; z++) {
		for (int x = 0; x < EL; x++) {
			if (set[x][z]) {
				fprintf(stderr, "X");
			}
			else { fprintf(stderr, "O"); };
		}
		fprintf(stderr, "\n");
	}*/

	for (int z = 0; z < EL - 1; ++z) {
		for (int x = 0; x < EL - 1; ++x) {
			// top left triangle
			vertices.push_back((float)x * scale);
			vertices.push_back(hm[x][z]);
			vertices.push_back((float)z * scale);

			vertices.push_back((float)x * scale);
			vertices.push_back(hm[x][z + 1]);
			vertices.push_back((float)z * scale);

			vertices.push_back((float)x * scale);
			vertices.push_back(hm[x + 1][z]);
			vertices.push_back((float)z * scale);

			// bottom right triangle
			vertices.push_back((float)x * scale);
			vertices.push_back(hm[x + 1][z + 1]);
			vertices.push_back((float)z * scale);

			vertices.push_back((float)x * scale);
			vertices.push_back(hm[x + 1][z]);
			vertices.push_back((float)z * scale);

			vertices.push_back((float)x * scale);
			vertices.push_back(hm[x][z + 1]);
			vertices.push_back((float)z * scale);
		}
	}

	for (int i = 0; i < ((EL - 1) * (EL - 1)) * 2; ++i) {
		indices.push_back(i);
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Terrain::~Terrain() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Terrain::generate() {
	int distance = EL / 2;
	offset = 10;
	while (true) {
		for (int x = 0; x < EL; x++) {
			for (int z = 0; z < EL; z++) {
				if (!set[x][z]) {
					if (inBounds(x - distance, z - distance) && set[x - distance][z - distance]) {
						generateDiamond(x, z, distance);
					}
				}
			}
		}
		for (int x = 0; x < EL; x++) {
			for (int z = 0; z < EL; z++) {
				if (!set[x][z]) {
					if (inBounds(x - distance, z) && set[x - distance][z]
						|| inBounds(x, z - distance) && set[x][z - distance]) {
						generateSquare(x, z, distance);
					}
				}
			}
		}
		distance = distance / 2;
		offset = offset - 1;
		//fprintf(stderr, "distance: %d, offset: %f\n", distance, offset);
		if (distance == 0) {
			fprintf(stderr, "done\n");
			break;
		}
	}
}

bool Terrain::inBounds(int x, int z) {
	return (x >= 0 && x < EL && z >= 0 && z < EL);
}

void Terrain::draw(GLuint shader) {
	glm::mat4 MVP = Window::P * Window::V * toWorld;

	glUseProgram(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "MVP"), 1, GL_FALSE, &MVP[0][0]);

	fprintf(stdout, "drawing\n");

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Terrain::generateDiamond(int x, int z, int d) {
	float sum = 0;
	float count = 0;
	
	int xx = x - d;
	int zz = z - d;
	if (inBounds(xx, zz)) {
		if (!set[xx, zz]) {
			fprintf(stderr, "shit at (%d, %d)\n", xx, zz);
		}
		sum = sum + hm[xx][zz];
		count = count + 1;
	}
	xx = x + d;
	zz = z - d;
	if (inBounds(xx, zz)) {
		if (!set[xx, zz]) {
			fprintf(stderr, "shit at (%d, %d)\n", xx, zz);
		}
		sum = sum + hm[xx][zz];
		count = count + 1;
	}
	xx = x - d;
	zz = z + d;
	if (inBounds(xx, zz)) {
		if (!set[xx, zz]) {
			fprintf(stderr, "shit at (%d, %d)\n", xx, zz);
		}
		sum = sum + hm[xx][zz];
		count = count + 1;
	}
	xx = x + d;
	zz = z + d;
	if (inBounds(xx, zz)) {
		if (!set[xx, zz]) {
			fprintf(stderr, "shit at (%d, %d)\n", xx, zz);
		}
		sum = sum + hm[xx][zz];
		count = count + 1;
	}
	sum = sum / count;
	hm[x][z] = sum + (float)(rng() % offset) - ((float)offset)/2;
	set[x][z] = true;
}

void Terrain::generateSquare(int x, int z, int d) {
	float sum = 0;
	float count = 0;

	int xx = x - d;
	int zz = z;
	if (inBounds(xx, zz)) {
		if (!set[xx, zz]) {
			fprintf(stderr, "shit at (%d, %d)\n", xx, zz);
		}
		sum = sum + hm[xx][zz];
		count = count + 1;
	}
	xx = x + d;
	zz = z;
	if (inBounds(xx, zz)) {
		if (!set[xx, zz]) {
			fprintf(stderr, "shit at (%d, %d)\n", xx, zz);
		}
		sum = sum + hm[xx][zz];
		count = count + 1;
	}
	xx = x;
	zz = z - d;
	if (inBounds(xx, zz)) {
		if (!set[xx, zz]) {
			fprintf(stderr, "shit at (%d, %d)\n", xx, zz);
		}
		sum = sum + hm[xx][zz];
		count = count + 1;
	}
	xx = x;
	zz = z + d;
	if (inBounds(xx, zz)) {
		if (!set[xx, zz]) {
			fprintf(stderr, "shit at (%d, %d)\n", xx, zz);
		}
		sum = sum + hm[xx][zz];
		count = count + 1;
	}
	sum = sum / count;
	hm[x][z] = sum + (float)(rng() % offset) - ((float)offset) / 2;
	set[x][z] = true;
}