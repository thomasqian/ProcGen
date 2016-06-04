#version 330 core

out vec4 color;

uniform sampler2D logs;
uniform sampler2D shingles;

in vec2 uv;
in float height;

void main() {
	if (height <= 1) {
		color = texture2D(logs, uv);
	} else {
		color = texture2D(shingles, uv);
	}
	//color = vec4(0.33, 0.17, 0.17, 1);
}