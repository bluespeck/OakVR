struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

PixelInputType OakVertexShader(VertexInputType input)
{
    PixelInputType output;
    
    output.position = input.position;
    
    // Store the texture coordinates for the pixel shader.
    output.tex = input.tex;
    
    return output;
}
