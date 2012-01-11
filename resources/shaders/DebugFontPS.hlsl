Texture2D fontTexture;
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
	
	color = fontTexture.Sample(SampleType, input.tex);
	
	if(color.r < 0.1f)
	{
		discard;
	}
	else
	{
		color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	return color;
}
