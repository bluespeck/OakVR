#version 420 core

in vec2 TexCoord0;
in vec3 Color;

uniform sampler2D texDiffuse0;

void main(void)
{	
	vec4 diffuseColor = vec4(Color, texture(texDiffuse0, TexCoord0).r);
	 
	gl_FragColor = diffuseColor;
}