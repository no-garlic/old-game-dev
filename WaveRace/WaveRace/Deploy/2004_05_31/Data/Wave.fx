
float4x4 WorldViewProj : WORLDVIEWPROJ;

sampler  DiffuseSampler;

struct VS_OUTPUT
{
    float4 Position  : POSITION;
    float4 Diffuse   : COLOR0;
    float2 TexCoord0 : TEXCOORD0;
    float2 TexCoord1 : TEXCOORD1;
};

struct PS_OUTPUT
{
    float4 RGBColor : COLOR0;
};

VS_OUTPUT VertexShader(float4 Position   : POSITION, 
                       float4 Diffuse    : COLOR0,
                       float2 TexCoord0  : TEXCOORD0,
                       float2 TexCoord1  : TEXCOORD1)
{
    VS_OUTPUT Out   = (VS_OUTPUT) 0;
    
    Out.Position    = mul(Position, WorldViewProj);
    Out.Diffuse     = Diffuse;
    Out.TexCoord0   = TexCoord0;
    Out.TexCoord1   = TexCoord1;

    return Out;
}

PS_OUTPUT PixelShader(VS_OUTPUT In) : COLOR
{
    PS_OUTPUT Out   = (PS_OUTPUT) 0;
    
    float4 color1   = tex2D(DiffuseSampler, In.TexCoord0) * In.Diffuse * 1.5;
    float4 color2   = tex2D(DiffuseSampler, In.TexCoord1) * 0.1;
    
    color1.a        = 0.85;
    color2.a        = 0.0;
    
    Out.RGBColor    = color1 + color2;
    
    return Out;
}
