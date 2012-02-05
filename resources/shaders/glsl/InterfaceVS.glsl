varying vec2 texCoords;
void main(void)
{
	gl_Position = gl_Vertex;
    texCoords = vec2(gl_MultiTexCoord0);
}