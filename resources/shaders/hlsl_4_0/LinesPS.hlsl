struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

float4 OakPixelShader(PixelInputType input) : SV_TARGET
{
	float4 color;
	
	// Sample the texture pixel at this location.
	color = input.color;
	
	return color;
}
