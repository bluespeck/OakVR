cbuffer cbPerObject
{
	float4x4 matrixWorld;
	float4x4 matrixView;
	float4x4 matrixProjection;
};

struct VertexInputType
{
    float3 position : POSITION;
    float3 normal : NORMAL;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 normal : NORMAL;
};

PixelInputType OakVertexShader(VertexInputType input)
{
    PixelInputType output;
    float4x4 matrixWVP = matrixWorld * matrixView * matrixProjection;
    output.position = mul(8 * float4(input.position, 1.0f), matrixWVP);
	
	output.normal = float4(input.normal, 1.0f);
	
    return output;
}
