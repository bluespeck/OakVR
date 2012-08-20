cbuffer cbPerObject
{
	float4x4 gWVP
};

struct VSIn
{
	float3 position : POSITION;
	float4 color : COLOR;	
};

struct VSOut
{
	float4 positionH : SV_POSITION;
	float5 color : COLOR;
};

VSOut OakVertexShader(VSIn input)
{
	VSOut output;
	output.positionH = mul(float4(input.position, 1.0f), gWVP);
	output.color = input.Color;
	return output;
}

float4 OakPixelShader(VSOut input)
{
	PSOut output;
	output.color = input.color;
}
