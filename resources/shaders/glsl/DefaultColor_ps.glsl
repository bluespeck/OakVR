#version 420 core

in vec3 Color;

uniform sampler2D texDiffuse0;

void main(void)
{	
	gl_FragColor = vec4(Color, 1.0);
}