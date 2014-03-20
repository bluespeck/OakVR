#version 420

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

in vec3 in_Position;
//in vec2 in_TexCoord;
out vec4 out_Color;
void main(void)
{
	gl_Position = vec4(-.2, -.5, .3, 1.0) + projectionMatrix * modelMatrix * vec4(0.25 * in_Position , 1.0);
	//gl_Position = vec4(in_Position , 1.0);
	out_Color = vec4(1.0, 0.0, 0.0, 1.0);
}


