
// ----------------------------------------------------------------------------
// Camera Parameters
// ----------------------------------------------------------------------------
float4x4 matrix_WorldViewProj;
float4x4 matrix_World;


// ----------------------------------------------------------------------------
// Light Parameters
// ----------------------------------------------------------------------------
float3 light0_Direction;
float3 light0_Diffuse;
float3 light0_Ambient;
float4 global_Ambient;


// ----------------------------------------------------------------------------
// Texture Parameters
// ----------------------------------------------------------------------------
texture tex_Diffuse;


// ----------------------------------------------------------------------------
// Texture sampler
// ----------------------------------------------------------------------------
sampler DiffuseSampler = sampler_state
{
  Texture   = <tex_Diffuse>;
  MipFilter = LINEAR;
  MinFilter = LINEAR;
  MagFilter = LINEAR;
};


// ----------------------------------------------------------------------------
// Vertex shader input
// ----------------------------------------------------------------------------
struct VS_INPUT
{
  float4 Position   : POSITION;   // Vertex position
  float3 Normal     : NORMAL;     // Vertex normal
  float2 TextureUV  : TEXCOORD0;  // Texture coords
};


// ----------------------------------------------------------------------------
// Vertex shader output
// ----------------------------------------------------------------------------
struct VS_OUTPUT
{
  float4 Position   : POSITION;   // Vertex position 
  float4 Diffuse    : COLOR0;     // Diffuse color
  float2 TextureUV  : TEXCOORD0;  // Texture coords 
};


//--------------------------------------------------------------------------------------
// Pixel shader output 
//--------------------------------------------------------------------------------------
struct PS_OUTPUT
{
  float4 RGBColor   : COLOR0;   // Pixel color    
};


// ----------------------------------------------------------------------------
// The vertex shader
// ----------------------------------------------------------------------------
VS_OUTPUT VertexShader(VS_INPUT In)
{
  VS_OUTPUT Out = (VS_OUTPUT) 0;
  
  // Transform the position into homogeneous projection space
  Out.Position = mul(In.Position, matrix_WorldViewProj);
  
  // Transform the normal from object space to world space
  float3 NormalWorldSpace = normalize(mul(In.Normal, (float3x3) matrix_World));
  
  // Calculate the diffuse color
  Out.Diffuse.rgb = saturate(dot(NormalWorldSpace, light0_Direction) * light0_Diffuse) + light0_Ambient + global_Ambient;
  Out.Diffuse.a   = 1.0;

  // Copy the texture coordinates through
  Out.TextureUV = In.TextureUV;
  
  // Return the output  
  return Out;
}


// ----------------------------------------------------------------------------
// The pixel shader
// ----------------------------------------------------------------------------
PS_OUTPUT PixelShader(VS_OUTPUT In)
{
  PS_OUTPUT Out = (PS_OUTPUT) 0;
  
  // Sample the texture
  Out.RGBColor = tex2D(DiffuseSampler, In.TextureUV) * In.Diffuse;
  
  // Return the output
  return Out;
}


//--------------------------------------------------------------------------------------
// Technique
//--------------------------------------------------------------------------------------
technique Default
{
  pass P0
  {          
    CULLMODE = NONE;
    FILLMODE = SOLID;

    VertexShader = compile vs_1_1 VertexShader();
    PixelShader  = compile ps_1_1 PixelShader(); 
  }
}


// -- EOF

