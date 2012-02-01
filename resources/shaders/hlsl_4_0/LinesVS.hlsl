cbuffer cbPerObject
{
	float4x4 matrixWorld;
	float4x4 matrixView;
	float4x4 matrixProjection;
};

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
	output.position = mul(float4(input.position, 1.0f), matrixWorld);
	output.position = mul(output.position, matrixView);
	output.position = mul(output.position, matrixProjection);
	
	output.color = input.color;
	
	return output;
}