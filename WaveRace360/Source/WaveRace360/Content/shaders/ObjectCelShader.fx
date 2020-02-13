
float4x4  m_worldViewProjection;
float4x4  m_world;
float3    m_lightDirection;
texture   m_celTexture;
float     m_edgeOffset;


sampler TextureSampler = sampler_state
{
  MIPFILTER = LINEAR;
  MINFILTER = LINEAR;
  MAGFILTER = LINEAR;
};


sampler CelSampler = sampler_state
{
  Texture = <m_celTexture>;
  MIPFILTER = POINT;
  MINFILTER = POINT;
  MAGFILTER = POINT;
};


struct VertexShaderInput
{
  float4 m_position : POSITION0;
  float3 m_normal   : NORMAL0;
  float2 m_texcoord : TEXCOORD0;
};


struct VertexShaderOutput
{
  float4 m_position : POSITION0;
  float3 m_normal   : TEXCOORD1;
  float2 m_texcoord : TEXCOORD0;
};


struct PixelShaderOutput
{
  float4 m_color    : COLOR0;
};


VertexShaderOutput VertexShader_Color(VertexShaderInput input)
{
  VertexShaderOutput output;

  output.m_position = mul(input.m_position, m_worldViewProjection);
  output.m_normal   = mul(input.m_normal, m_world);
  output.m_texcoord = input.m_texcoord;

  return output;
}


PixelShaderOutput PixelShader_Color(VertexShaderOutput input)
{
  PixelShaderOutput output;

  float3 normal	    = normalize(input.m_normal);
  float nDotL       = dot(normal, -m_lightDirection);
  float4 baseColor  = tex2D(TextureSampler, input.m_texcoord);
  float  celValue   = clamp(nDotL, 0.0f, 1.0f);
  float2 celCoord   = float2(celValue, celValue);
  float4 celColor   = tex2D(CelSampler, celCoord);
  output.m_color    = baseColor * celColor;

  return output;
}


VertexShaderOutput VertexShader_Outline(VertexShaderInput input)
{
  VertexShaderOutput output;

  output.m_position = mul(input.m_position, m_worldViewProjection) + (mul(m_edgeOffset, mul(input.m_normal, m_worldViewProjection)));
  output.m_normal   = mul(input.m_normal, m_world);
  output.m_texcoord = input.m_texcoord;

  return output;
}


PixelShaderOutput PixelShader_Outline()
{
  PixelShaderOutput output;

  output.m_color = float4(0.0f, 0.0f, 0.0f, 1.0f);

  return output;
}


technique T1
{
//  pass P1
//  {
//    VertexShader  = compile vs_2_0 VertexShader_Outline();
//    PixelShader   = compile ps_2_0 PixelShader_Outline();
//    ZWriteEnable  = false;
//    CullMode      = None;
//  }
  pass P2
  {
    VertexShader  = compile vs_2_0 VertexShader_Color();
    PixelShader   = compile ps_2_0 PixelShader_Color();
//    ZWriteEnable  = true;
  }
}


