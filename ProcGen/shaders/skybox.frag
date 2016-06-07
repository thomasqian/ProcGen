#version 330 core

in vec3 TexCoords;
out vec4 color;

uniform vec3 view2;
uniform samplerCube skybox;

void main()
{    
    color = texture(skybox, TexCoords);
	color = vec4(color.r*view2.r, color.g*view2.g, color.b*view2.b, 1);
}