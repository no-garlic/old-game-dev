
float4x4  m_worldViewProjection;
float4x4  m_world;
float3    m_lightDirection;


sampler TextureSampler = sampler_state
{
  MIPFILTER = LINEAR;
  MINFILTER = LINEAR;
  MAGFILTER = LINEAR;
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
  output.m_color    = tex2D(TextureSampler, input.m_texcoord) * float4(nDotL, nDotL, nDotL, 1.0f);

  return output;
}


technique T1
{
  pass P1
  {
    VertexShader  = compile vs_2_0 VertexShader_Color();
    PixelShader   = compile ps_2_0 PixelShader_Color();
  }
}

