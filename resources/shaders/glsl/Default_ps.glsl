#version 330 core

in vec2 TexCoord0;
//in vec3 Color;

uniform sampler2D texDiffuse0;

void main(void)
{	
	vec4 diffuseColor = texture(texDiffuse0, TexCoord0);
	 
	gl_FragColor = diffuseColor;
}