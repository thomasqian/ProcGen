#version 330 core

out vec4 color;
in float height;
in vec2 uv;

uniform sampler2D sand;
uniform sampler2D grass;
uniform sampler2D snow;

uniform int style;
uniform float min;
uniform float max;

uniform vec3 point;
uniform vec3 view;

void main() {
	float alt = (height-min)/(max-min); //apprx 0-1
	if(style == 2){
		color = vec4(alt, alt, alt, 1);
	}
	else if(style == 1){
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
	else{
		float sandW = 0;
		float grassW = 0;
		float snowW = 0;

		sandW = 3-10*alt;
		if(alt<0.5){
			grassW = -2+10*alt;
		}
		else{
			grassW = 8-10*alt;
		}
		snowW = -7+10*alt;
	
		sandW = max(0, min(1, sandW));
		grassW = max(0, min(1, grassW));
		snowW = max(0, min(1, snowW));

		vec4 sandC = texture2D(sand, uv);
		vec4 grassC = texture2D(grass, uv);
		vec4 snowC = texture2D(snow, uv);
	
		sandC = sandC*sandW;
		grassC = grassC*grassW;
		snowC = snowC*snowW;

		color = sandC+grassC+snowC;
	}
	color = vec4(color.r*view.r, color.g*view.g, color.b*view.b, 1);
}