#version 330 core

out vec4 color;

uniform sampler2D logs;
uniform sampler2D shingles;

in vec3 fragPos;
in float height;
in vec3 fragNormal;

vec2 tex;

void main() {
	if (fragNormal.x >= fragNormal.y && fragNormal.x >= fragNormal.y) {
		tex.y = fragPos.y;
		tex.x = fragPos.z;
	} else if (fragNormal.y >= fragNormal.x && fragNormal.y >= fragNormal.z) {
		tex.y = fragPos.x;
		tex.x = fragPos.z;
	} else	if (fragNormal.z >= fragNormal.x && fragNormal.z >= fragNormal.y) {
		tex.y = fragPos.x;
		tex.x = fragPos.y;
	}

	if (fragNormal.y == 0.0) {
		color = texture2D(logs, tex);
	} else {
		color = texture2D(shingles, tex);
	}
	//color = vec4(fragNormal, 1.0);
	//color = vec4(0.33, 0.17, 0.17, 1);
}