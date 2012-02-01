struct VertexInputType
{
    float3 position : POSITION;
    float3 normal : NORMAL;
};

struct PixelInputType
{
    float4 position : POSITION;
    float4 normal : COLOR;
};

PixelInputType OakVertexShader(VertexInputType input)
{
    PixelInputType output;
    
    output.position = mul(float4(input.position, 1.0f), gWVP);
	
	output.normal = float4(input.normal, 1.0f);
	
    return output;
}
