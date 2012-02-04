cbuffer cbPerObject
{
	float4x4 matrixWorld;
	float4x4 matrixView;
	float4x4 matrixProjection;
};

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
    float4x4 matrixWVP = matrixWorld * matrixView * matrixProjection;
    //output.position = float4(0.0f, 0.0f, 0.0f, 1.0f);
	//output.position = float4(input.position, 1.0f);
	output.position = mul(float4(input.position, 1.0f), matrixWVP);
	//output.position = mul(float4(input.position, 1.0f), matrixView);
	//output.position = mul(float4(input.position, 1.0f), matrixWorld);
	//output.position = mul(float4(input.position, 1.0f), matrixWorld);
	//output.position = mul(output.position, matrixView);
	
    return output;
}
