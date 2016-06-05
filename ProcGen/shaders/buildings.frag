#version 330 core

out vec4 color;

uniform sampler2D logs;
uniform sampler2D shingles;

in vec3 fragPos;
in float height;
in vec3 fragNormal;

vec2 tex;

void main() {	
	float x, y, z;
	x = fragNormal.x;
	y = fragNormal.y;
	z = fragNormal.z;
	if(x > 0 && x < 0.01){
		x = 0;
	}
	if(z > 0 && z < 0.01){
		z = 0;
	}
	if(x < 0 && x > -0.01){
		x = 0;
	}
	if(z < 0 && z > -0.01){
		z = 0;
	}
	if (x != 0 && y == 0 && z == 0) {
		tex.x = fragPos.z;
		tex.y = fragPos.y;
	}
	else if (y != 0) {
		tex.x = fragPos.x;
		tex.y = fragPos.z;
	}
	else if (x == 0 && y == 0 && z != 0) {
		tex.x = fragPos.x;
		tex.y = fragPos.y;
	}

	if (fragNormal.y == 0) {
		color = texture2D(logs, tex);
	} else {
		color = texture2D(shingles, tex);
	}
}