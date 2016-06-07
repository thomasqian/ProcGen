#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 MVP;
uniform mat4 model;
uniform mat4 modelUnscaled;

out float height;
out vec3 fragNormal;
out vec3 fragPosU;
out vec3 fragPos;

void main() {
    gl_Position = MVP * vec4(position, 1.0);
	fragNormal = mat3(transpose(inverse(model))) * normal;
	fragPosU = mat3(transpose(inverse(modelUnscaled)))*position;
	fragPos = mat3(transpose(inverse(model)))*position;
	height = position.y;
}
