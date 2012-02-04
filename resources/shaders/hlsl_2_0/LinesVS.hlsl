shared uniform extern float4x4 gViewProj:VIEWPROJECTION;

struct VertexInputType
{
    float3 position : POSITION;
    float4 color : COLOR;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

PixelInputType OakVertexShader(VertexInputType input)
{
    PixelInputType output;
	output.position = mul(float4(input.position, 1.0f), gViewProj);
	
	output.color = input.color;
	
	return output;
}