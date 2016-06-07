#include "Terrain.h"

std::mt19937_64 rng(time(NULL));
glm::mat4 toWorld(1.0f);

Terrain::Terrain() {

	for (int x = 0; x < EL; ++x) {
		for (int z = 0; z < EL; ++z) {
			set[x][z] = false;
			flat[x][z] = false;
			paved[x][z] = false;
		}
	}

	hm[0][0] = rng() % (int)initialOffset;
	hm[0][EL-1] = rng() % (int)initialOffset;
	hm[EL-1][0] = rng() % (int)initialOffset;
	hm[EL-1][EL-1] = rng() % (int)initialOffset;

	set[0][0] = true;
	set[0][EL-1] = true;
	set[EL-1][0] = true;
	set[EL-1][EL-1] = true;
	
	generate();

	identify();
	
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

	style = 0;
	min = hm[0][0];
	max = hm[0][0];
	for (int z = 0; z < EL; z++) {
		for (int x = 0; x < EL; x++) {
			if(hm[x][z] < min){
				min = hm[x][z];
			}
			else if(hm[x][z] > max){
				max = hm[x][z];
			}
		}
	}
	fprintf(stderr, "Min: %.2f, Max: %.2f\n", min, max);

	bool topLeft = true;
	for (int z = 0; z < EL - 1; ++z) {
		for (int x = 0; x < EL - 1; ++x) {
			if(topLeft){
				// top left triangle
				vertices.push_back((float)x * scale);
				vertices.push_back(hm[x][z]);
				vertices.push_back((float)z * scale);

				vertices.push_back((float)x * scale);
				vertices.push_back(hm[x][z + 1]);
				vertices.push_back((float)(z + 1) * scale);

				vertices.push_back((float)(x + 1) * scale);
				vertices.push_back(hm[x + 1][z]);
				vertices.push_back((float)z * scale);

				// bottom right triangle
				vertices.push_back((float)(x + 1) * scale);
				vertices.push_back(hm[x + 1][z + 1]);
				vertices.push_back((float)(z + 1) * scale);

				vertices.push_back((float)(x + 1) * scale);
				vertices.push_back(hm[x + 1][z]);
				vertices.push_back((float)z * scale);

				vertices.push_back((float)x * scale);
				vertices.push_back(hm[x][z + 1]);
				vertices.push_back((float)(z + 1) * scale);
			}
			else{
				// top right triangle
				vertices.push_back((float)x * scale);
				vertices.push_back(hm[x][z]);
				vertices.push_back((float)z * scale);

				vertices.push_back((float)(x + 1) * scale);
				vertices.push_back(hm[x + 1][z + 1]);
				vertices.push_back((float)(z + 1) * scale);

				vertices.push_back((float)(x + 1) * scale);
				vertices.push_back(hm[x + 1][z]);
				vertices.push_back((float)z * scale);

				// bottom left triangle
				vertices.push_back((float)x * scale);
				vertices.push_back(hm[x][z]);
				vertices.push_back((float)z * scale);

				vertices.push_back((float)x * scale);
				vertices.push_back(hm[x][z + 1]);
				vertices.push_back((float)(z + 1) * scale);

				vertices.push_back((float)(x + 1) * scale);
				vertices.push_back(hm[x + 1][z + 1]);
				vertices.push_back((float)(z + 1) * scale);
			}
			topLeft = !topLeft;
		}
	}

	float top = (float)(EL-1) * scale;
	for (int z = 0; z < EL - 1; ++z){
		//first triangle bottom
		vertices.push_back(0.0f); vertices.push_back(hm[0][z]); vertices.push_back((float)z * scale);
		vertices.push_back(0.0f); vertices.push_back(min); vertices.push_back((float)z * scale);
		vertices.push_back(0.0f); vertices.push_back(min); vertices.push_back((float)(z+1) * scale);

		//second triangle bottom
		vertices.push_back(0.0f); vertices.push_back(hm[0][z]); vertices.push_back((float)z * scale);
		vertices.push_back(0.0f); vertices.push_back(min); vertices.push_back((float)(z+1) * scale);
		vertices.push_back(0.0f); vertices.push_back(hm[0][z+1]); vertices.push_back((float)(z+1) * scale);

		//first triangle top
		vertices.push_back(top); vertices.push_back(hm[EL-1][z]); vertices.push_back((float)z * scale);
		vertices.push_back(top); vertices.push_back(min); vertices.push_back((float)(z+1) * scale);
		vertices.push_back(top); vertices.push_back(min); vertices.push_back((float)z * scale);

		//second triangle top
		vertices.push_back(top); vertices.push_back(hm[EL-1][z]); vertices.push_back((float)z * scale);
		vertices.push_back(top); vertices.push_back(hm[EL-1][z+1]); vertices.push_back((float)(z+1) * scale);
		vertices.push_back(top); vertices.push_back(min); vertices.push_back((float)(z+1) * scale);
	}
	for (int x = 0; x < EL - 1; ++x){
		//first triangle bottom
		vertices.push_back((float)x * scale); vertices.push_back(hm[x][0]); vertices.push_back(0.0f);
		vertices.push_back((float)(x+1) * scale); vertices.push_back(min); vertices.push_back(0.0f);
		vertices.push_back((float)x * scale); vertices.push_back(min); vertices.push_back(0.0f);

		//second triangle bottom
		vertices.push_back((float)x * scale); vertices.push_back(hm[x][0]); vertices.push_back(0.0f);
		vertices.push_back((float)(x+1) * scale); vertices.push_back(hm[x+1][0]); vertices.push_back(0.0f);
		vertices.push_back((float)(x+1) * scale); vertices.push_back(min); vertices.push_back(0.0f);

		//first triangle top
		vertices.push_back((float)x * scale); vertices.push_back(hm[x][EL-1]); vertices.push_back(top);
		vertices.push_back((float)x * scale); vertices.push_back(min); vertices.push_back(top);
		vertices.push_back((float)(x+1) * scale); vertices.push_back(min); vertices.push_back(top);

		//second triangle top
		vertices.push_back((float)x * scale); vertices.push_back(hm[x][EL-1]); vertices.push_back(top);
		vertices.push_back((float)(x+1) * scale); vertices.push_back(min); vertices.push_back(top);
		vertices.push_back((float)(x+1) * scale); vertices.push_back(hm[x+1][EL-1]); vertices.push_back(top);
	}


	for (int i = 0; i < (EL - 1) * (EL - 1) * 6 + (EL-1)*24; ++i) {
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
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	Building::initTextures();
}

Terrain::~Terrain() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	for (int i = 0; i < buildings.size(); ++i) delete(buildings[i]);

	Building::freeTextures();
}

void Terrain::generate() {
	int distance = EL / 2;
	float offset = initialOffset;
	while (true) {
		fprintf(stderr, "distance: %d, offset: %f\n", distance, offset);
		for (int z = 0; z < EL; z++) {
			for (int x = 0; x < EL; x++) {
				if (!set[x][z]) {
					if (inBounds(x - distance, z - distance) && set[x - distance][z - distance]) {
						generateDiamond(x, z, distance, offset);
					}
				}
			}
		}
		for (int z = 0; z < EL; z++) {
			for (int x = 0; x < EL; x++) {
				if (!set[x][z]) {
					if (inBounds(x - distance, z) && set[x - distance][z]
						|| inBounds(x, z - distance) && set[x][z - distance]) {
						generateSquare(x, z, distance, offset);
					}
				}
			}
		}
		distance = distance/2;
		offset = offset/2;
		if(offset<1.0f){offset = 1.0f;}
		if (distance == 0) {
			break;
		}
	}
	fprintf(stderr, "done\n");
}

void Terrain::identify() {
	int flatCount = 0;
	for (int z = 0; z < EL - 3; z++) {
		for (int x = 0; x < EL - 3; x++) {
			if (!flat[x][z] && !flat[x+1][z] && !flat[x+2][z] && !flat[x+3][z] &&
				!flat[x][z+3] && !flat[x+1][z+3] && !flat[x+2][z+3] && !flat[x+3][z+3] &&
				!flat[x][z+1] && !flat[x][z+2] && !flat[x+3][z+1] && !flat[x+3][z+2]) {
				float avg = (hm[x][z]+hm[x+3][z]+hm[x][z+3]+hm[x+3][z+3])/4.0f;
				if (abs(hm[x][z]-avg) < flatRange && abs(hm[x+3][z]-avg) < flatRange &&
					abs(hm[x][z+3]-avg) < flatRange && abs(hm[x+3][z+3]-avg) < flatRange){
					flatCount++;
					for (int zz = z; zz <= z + 3; zz++){
						for (int xx = x; xx <= x + 3; xx++){
							hm[xx][zz] = avg;
							flat[xx][zz] = true;
						}
					}
					paved[x][z] = true;
					buildings.push_back(new Building(((float)x+1.5f) * scale, hm[x][z], ((float)z+1.5f) * scale, scale));
				}
			}
		}
	}
	fprintf(stderr, "Flat Count: %d\n", flatCount);
}

bool Terrain::inBounds(int x, int z) {
	return (x >= 0 && x < EL && z >= 0 && z < EL);
}

void Terrain::draw(GLuint shader, GLuint buildingShader, glm::vec3 point, glm::vec3 view) {
	glm::mat4 MVP = Window::P * Window::V * toWorld;

	glUniformMatrix4fv(glGetUniformLocation(shader, "MVP"), 1, GL_FALSE, &MVP[0][0]);

	glUniform1i(glGetUniformLocation(shader, "style"), style);
	glUniform1f(glGetUniformLocation(shader, "min"), min);
	glUniform1f(glGetUniformLocation(shader, "max"), max);

	glUniform3f(glGetUniformLocation(shader, "point"), point.x, point.y, point.z);
	glUniform3f(glGetUniformLocation(shader, "view"), view.x, view.y, view.z);

	glUniform1f(glGetUniformLocation(shader, "length"), (float)((float)EL * (float)scale));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glCullFace(GL_FRONT);
	for (int i = 0; i < buildings.size(); i++) {
		buildings[i]->draw(buildingShader, min, max, point, view);
	}
}

void Terrain::generateDiamond(int x, int z, int d, float o) {
	float sum = 0;
	float count = 0;
	
	int xx = x - d;
	int zz = z - d;
	if (inBounds(xx, zz)) {
		if (!set[xx][zz]) {
			fprintf(stderr, "D break (%d, %d)\n", xx, zz);
			return;
		}
		sum = sum + hm[xx][zz];
		count = count + 1;
	}
	xx = x + d;
	zz = z - d;
	if (inBounds(xx, zz)) {
		if (!set[xx][zz]) {
			fprintf(stderr, "D break (%d, %d)\n", xx, zz);
			return;
		}
		sum = sum + hm[xx][zz];
		count = count + 1;
	}
	xx = x - d;
	zz = z + d;
	if (inBounds(xx, zz)) {
		if (!set[xx][zz]) {
			fprintf(stderr, "D break (%d, %d)\n", xx, zz);
			return;
		}
		sum = sum + hm[xx][zz];
		count = count + 1;
	}
	xx = x + d;
	zz = z + d;
	if (inBounds(xx, zz)) {
		if (!set[xx][zz]) {
			fprintf(stderr, "D break (%d, %d)\n", xx, zz);
			return;
		}
		sum = sum + hm[xx][zz];
		count = count + 1;
	}
	sum = sum / count;
	hm[x][z] = sum + (float)(rng() % (int)o) - o/2;
	set[x][z] = true;
}

void Terrain::generateSquare(int x, int z, int d, float o) {
	float sum = 0;
	float count = 0;

	int xx = x - d;
	int zz = z;
	if (inBounds(xx, zz)) {
		if (!set[xx][zz]) {
			fprintf(stderr, "S break (%d, %d)\n", xx, zz);
			return;
		}
		sum = sum + hm[xx][zz];
		count = count + 1;
	}
	xx = x + d;
	zz = z;
	if (inBounds(xx, zz)) {
		if (!set[xx][zz]) {
			fprintf(stderr, "S break (%d, %d)\n", xx, zz);
			return;
		}
		sum = sum + hm[xx][zz];
		count = count + 1;
	}
	xx = x;
	zz = z - d;
	if (inBounds(xx, zz)) {
		if (!set[xx][zz]) {
			fprintf(stderr, "S break (%d, %d)\n", xx, zz);
			return;
		}
		sum = sum + hm[xx][zz];
		count = count + 1;
	}
	xx = x;
	zz = z + d;
	if (inBounds(xx, zz)) {
		if (!set[xx][zz]) {
			fprintf(stderr, "S break (%d, %d)\n", xx, zz);
			return;
		}
		sum = sum + hm[xx][zz];
		count = count + 1;
	}
	sum = sum / count;
	hm[x][z] = sum + (float)(rng() % (int)o) - o/2;
	set[x][z] = true;
}

void Terrain::toggle(){
	style = (style + 1) % 3;
}