#version 430

in vec3 in_Position;

void main(void)
{
	gl_Position = vec4(2 * in_Position, 1.0);
	gl_Color = vec4(1.0, 1.0, 1.0, 1.0);
}


