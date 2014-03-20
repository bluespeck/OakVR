#version 420

in vec3 pass_Color;

void main(void)
{
	gl_FragColor = vec4(pass_Color, 1.0);
}


