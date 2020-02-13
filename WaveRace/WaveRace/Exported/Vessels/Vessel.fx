
float4x4 WorldViewProj : WORLDVIEWPROJ;

sampler  DiffuseSampler;

struct VS_OUTPUT
{
    float4 Position : POSITION;
    float4 Diffuse  : COLOR0;
    float2 TexCoord : TEXCOORD0;
};

struct PS_OUTPUT
{
    float4 RGBColor : COLOR0;
};

VS_OUTPUT VertexShader(float4 Position   : POSITION, 
                       float4 Diffuse    : COLOR0,
                       float2 TexCoord   : TEXCOORD0)
{
    VS_OUTPUT Out   = (VS_OUTPUT) 0;
    
    Out.Position    = mul(Position, WorldViewProj);
    Out.Diffuse     = Diffuse;
    Out.TexCoord    = TexCoord;

    return Out;
}

PS_OUTPUT PixelShader(VS_OUTPUT In) : COLOR
{
    PS_OUTPUT Out   = (PS_OUTPUT) 0;
    
    Out.RGBColor    = tex2D(DiffuseSampler, In.TexCoord) * In.Diffuse;
    
    return Out;
}
