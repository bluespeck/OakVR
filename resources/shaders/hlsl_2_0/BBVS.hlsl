shared uniform extern float4x4 gViewProj:VIEWPROJECTION;
//uniform extern float4x4 gWorld:WORLD;

struct VertexInputType
{
    float3 position : POSITION;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
};

PixelInputType OakVertexShader(VertexInputType input)
{
    PixelInputType output;
	output.position = mul(float4(input.position, 1.0f), gViewProj);
	//output.position = float4(input.position, 1.0f);
    return output;
}
