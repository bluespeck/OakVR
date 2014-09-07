#version 420 core

in vec4 Color;

uniform sampler2D texDiffuse0;

void main(void)
{	
	gl_FragColor = Color, 1.0;
}