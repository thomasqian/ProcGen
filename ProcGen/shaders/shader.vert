#version 330 core

layout (location = 0) in vec3 position;

uniform float length;
uniform mat4 MVP;
out float height;
out vec2 uv;

void main() {
    gl_Position = MVP * vec4(position, 1.0);
	height = position.y;
	uv = vec2(position.x / length, position.z / length);
}
