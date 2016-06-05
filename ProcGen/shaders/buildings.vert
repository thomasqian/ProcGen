#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 MVP;

out float height;
out vec3 fragNormal;
out vec3 fragPos;

void main() {
    gl_Position = MVP * vec4(position, 1.0);
	fragNormal = normalize(mat3(transpose(inverse(model))) * normal);
	fragPos = position;
	height = position.y;
}
