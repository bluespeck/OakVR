#version 420 core

in vec4 fColor;
out vec4 out_color;
uniform sampler2D texDiffuse0;

void main(void)
{	
	out_color = fColor;
}