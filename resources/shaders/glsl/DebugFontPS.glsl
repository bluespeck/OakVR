varying vec2 texCoords;
uniform sampler2D textureSampler;

void main(void)
{
	vec4 col = texture2D(textureSampler, texCoords);
	
	if( col.r > 0.1f)
		gl_FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	else
		discard;
}