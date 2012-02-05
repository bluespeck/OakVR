varying vec2 texCoords;
uniform sampler2D textureSampler;

void main(void)
{
	gl_FragColor = texture2D(textureSampler, texCoords);
}