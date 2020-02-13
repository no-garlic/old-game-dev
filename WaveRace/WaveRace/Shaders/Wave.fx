
texture tex0 < string name = "0"; >;
texture tex1 < string name = "1"; >;
texture tex2 < string name = "2"; >;

float4x4 WorldViewProj : WORLDVIEWPROJ;


sampler DiffuseSampler = sampler_state
{
    Texture   = (tex0);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};


sampler ShadowSampler1 = sampler_state
{
    Texture   = (tex1);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

sampler ShadowSampler2 = sampler_state
{
    Texture   = (tex2);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};


struct VS_OUTPUT
{
    float4 Position  : POSITION;
    float4 Diffuse   : COLOR0;
    float2 TexCoord0 : TEXCOORD0;
    float2 TexCoord1 : TEXCOORD1;
    float2 TexCoord2 : TEXCOORD2;
    float2 TexCoord3 : TEXCOORD3;
};

struct PS_OUTPUT
{
    float4 RGBColor : COLOR0;
};

VS_OUTPUT VS (float4 Position   : POSITION, 
              float4 Diffuse    : COLOR0,
              float2 TexCoord0  : TEXCOORD0,
              float2 TexCoord1  : TEXCOORD1)
{
    VS_OUTPUT Out   = (VS_OUTPUT) 0;
    
    Out.Position    = mul(Position, WorldViewProj);
    Out.Diffuse     = Diffuse;
    Out.TexCoord0   = TexCoord0;
    Out.TexCoord1   = TexCoord0;
    Out.TexCoord2   = TexCoord1;
    Out.TexCoord3   = TexCoord1;
    return Out;
}

PS_OUTPUT PS (VS_OUTPUT In) : COLOR
{
    PS_OUTPUT Out   = (PS_OUTPUT) 0;

    float4 color1   = tex2D(DiffuseSampler, In.TexCoord0) * In.Diffuse; // Color from wave normal
    float4 color2   = tex2D(ShadowSampler1, In.TexCoord1) * 0.2;        // Highlights on wave tips
    float4 color3   = tex2D(ShadowSampler2, In.TexCoord2) * 0.05;       // Random wave swells
    
    color1.a        = 0.85;
    color2.a        = 0.0;
    color3.a        = 0.0;
    
    Out.RGBColor    = color1 + color2 + color3;// + color4;
    
    return Out;
}


technique tec0
{
    pass p0
    {
        // Set up reasonable material defaults
        MaterialAmbient = {1.0, 1.0, 1.0, 1.0}; 
        MaterialDiffuse = {1.0, 1.0, 1.0, 1.0}; 
        MaterialSpecular = {1.0, 1.0, 1.0, 1.0}; 
        MaterialPower = 40.0f;
        
        // Turn lighting on and use light 0
        LightEnable[0] = False;
        Lighting = False;
        
        // Set up texture stage 0
        Texture[0] = <tex0>;
        Texture[1] = <tex1>;

        ColorOp[0] = Modulate;
        ColorArg1[0] = Texture;
        ColorArg2[0] = Diffuse;

        ColorOp[1] = Disable;
        ColorOp[1] = Modulate;
        ColorArg1[1] = Current;
        ColorArg2[1] = Texture;

        AlphaBlendEnable = True;
        SrcBlend        = SrcAlpha;
        DestBlend       = InvSrcAlpha;
        
        AlphaOp[0] = Modulate;
        AlphaArg1[0] = Texture;
        AlphaArg2[0] = Diffuse;

        AddressU[0]     = Wrap;
        AddressV[0]     = Wrap;
        MinFilter[0] = Linear;
        MagFilter[0] = Linear;
        MipFilter[0] = Linear;
        
        // Disable texture stage 1
        ColorOp[2] = Disable;
        AlphaOp[1] = Disable;
        
        VertexShader = compile vs_1_1 VS();
        PixelShader =  compile ps_1_1 PS();
    }
}
