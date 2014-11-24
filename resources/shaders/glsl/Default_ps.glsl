#version 420 core

in vec2 TexCoord0;
out vec4 color;

uniform sampler2D texDiffuse0;

void main(void)
{	
	vec4 diffuseColor = texture(texDiffuse0, TexCoord0);
	 
	color = diffuseColor;
}