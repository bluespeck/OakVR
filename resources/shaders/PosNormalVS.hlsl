struct VertexInputType
{
    float3 position : POSITION;
    float3 normal : NORMAL;
};

struct PixelInputType
{
    float4 position : POSITION;
    //float3 normal : NORMAL;
};

PixelInputType OakVertexShader(VertexInputType input)
{
    PixelInputType output;
    
    output.position = float4(input.position, 1.0f);
	//output.normal = input.normal;
	
    return output;
}
