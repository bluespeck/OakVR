struct PixelInputType
{
    float4 position : POSITION;
    float4 normal : COLOR;
};

float4 OakPixelShader(PixelInputType input) : SV_TARGET
{
	float4 color;
	
	// Sample the texture pixel at this location.
	color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	
	return color;
}
