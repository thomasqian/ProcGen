#version 330 core

out vec4 color;

uniform sampler2D wood;
uniform sampler2D shingles;
uniform sampler2D snowwall;
uniform sampler2D snowroof;
uniform sampler2D sandbrick;
uniform sampler2D strawroof;

uniform float min;
uniform float max;
uniform float ypos;

uniform vec3 point;
uniform vec3 view;

in vec3 fragPosU;
in vec3 fragPos;
in float height;
in vec3 fragNormal;

vec2 tex;

void main() {
	float alt = (ypos-min) / (max-min); //apprx 0-1

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
		tex.x = fragPosU.z;
		tex.y = fragPosU.y;
	}
	else if (y != 0) {
		tex.x = fragPosU.x;
		tex.y = fragPosU.z;
	}
	else if (x == 0 && y == 0 && z != 0) {
		tex.x = fragPosU.x;
		tex.y = fragPosU.y;
	}
	if (fragNormal.y == 0) {
		tex.x = tex.x/2+0.5;
		if (alt < 0.2) {
			color = texture2D(sandbrick, tex);
		} else if (alt < 0.7) {
			color = texture2D(wood, tex);
		} else {
			color = texture2D(snowwall, tex);
		}
	} else {
		if (alt < 0.2) {
			color = texture2D(strawroof, tex);
		} else if (alt < 0.7) {
			color = texture2D(snowroof, tex);
		} else {
			color = texture2D(shingles, tex);
		}
	}
	color = vec4(color.r*view.r, color.g*view.g, color.b*view.b, 1);
}