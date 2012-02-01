Texture2D interfaceTexture;
SamplerState SampleType
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

float4 OakPixelShader(PixelInputType input) : SV_TARGET
{
	float4 color;
	
	// Sample the texture pixel at this location.
	color = interfaceTexture.Sample(SampleType, input.tex);
	
	return color;
}
