#version 330 core

out vec4 color;
in float height;

float alt = 100 - 15 * height;

void main() {
    color = vec4(1.0f, alt/255.0f, 0.0f, 1.0f);
}
