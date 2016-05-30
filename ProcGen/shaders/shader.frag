#version 330 core

out vec4 color;
in float height;

uniform bool grayscale;
uniform float min;
uniform float max;

void main() {
	float alt = (height-min)/(max-min); //apprx 0-1
	if(grayscale){
		color = vec4(alt, alt, alt, 1);
	}
	else{
		float r = 0;
		float g = 0;
		float b = 0;
		r = 2-alt*4;
		b = -2+alt*4;
		if(alt<0.5){
			g = alt*4;
		}
		else{
			g = 4-alt*4;
		}
		r = max(0, min(1, r));
		g = max(0, min(1, g));
		b = max(0, min(1, b));
		color = vec4(r, g, b, 1);
	}
}