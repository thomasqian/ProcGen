#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 MVP;
out float height;
out vec2 uv;

void main() {
    gl_Position = MVP * vec4(position, 1.0);
	uv = vec2(position.x, position.z);
	height = position.y;
}
