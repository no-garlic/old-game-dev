
// Matrix
float4x4 World;
float4x4 View;
float4x4 Projection;
float4x4 matrix_WorldViewProj : WORLDVIEWPROJ;

// Parallel light
float3  LightDirection;

// Textures
texture texture_Color1;
texture texture_Color2;
texture texture_Color3;
texture texture_Blend;

// Texture coordinates
float texture_Color1_U;
float texture_Color1_V;
float texture_Color2_U;
float texture_Color2_V;
float texture_Color3_U;
float texture_Color3_V;
float texture_Blend_U;
float texture_Blend_V;

// Samplers
sampler textureSampler_Color1 = sampler_state
{
  Texture = <texture_Color1>;
  magfilter = LINEAR;
  minfilter = LINEAR;
  mipfilter = LINEAR;
};
sampler textureSampler_Color2 = sampler_state
{
  Texture = <texture_Color2>;
  magfilter = LINEAR;
  minfilter = LINEAR;
  mipfilter = LINEAR;
};
sampler textureSampler_Color3 = sampler_state
{
  Texture = <texture_Color3>;
  magfilter = LINEAR;
  minfilter = LINEAR;
  mipfilter = LINEAR;
};
sampler textureSampler_Blend = sampler_state
{
  Texture = <texture_Blend>;
  magfilter = LINEAR;
  minfilter = LINEAR;
  mipfilter = LINEAR;
};
sampler textureSampler_Cel = sampler_state
{
  Texture = <texture_Blend>;
  magfilter = POINT;
  minfilter = POINT;
  mipfilter = POINT;
};

// VS Input
struct gtVertex
{
  float4 Position : POSITION0;
  float3 Normal   : NORMAL0;

};

// PS Input
struct gtPixelFormat
{
  float4 pixelPosition            : POSITION0;
  float2 textureCoordinate_Color1 : TEXCOORD0;
  float2 textureCoordinate_Color2 : TEXCOORD1;
  float2 textureCoordinate_Color3 : TEXCOORD2;
  float2 textureCoordinate_Blend  : TEXCOORD3;
  float3 Normal                   : TEXCOORD4;
};

// PS Output
struct tScreenOutput
{
  float4 pixelColor : COLOR0;
};

// Vertex shader
void vertex_shader(in gtVertex IN, out gtPixelFormat OUT)
{
  OUT.pixelPosition = mul(IN.Position, matrix_WorldViewProj);
  OUT.textureCoordinate_Color1 = float2(IN.Position.x * texture_Color1_U, IN.Position.z * texture_Color1_V);
  OUT.textureCoordinate_Color2 = float2(IN.Position.x * texture_Color2_U, IN.Position.z * texture_Color2_V);
  OUT.textureCoordinate_Color3 = float2(IN.Position.x * texture_Color3_U, IN.Position.z * texture_Color3_V);
  OUT.textureCoordinate_Blend  = float2(IN.Position.x * texture_Blend_U,  IN.Position.z * texture_Blend_V);
  OUT.Normal                   = mul(IN.Normal, World);
}

// Pixel shader
void pixel_shader(in gtPixelFormat IN, out tScreenOutput OUT)
{
  float4 color1 = tex2D(textureSampler_Color1, IN.textureCoordinate_Color1);
  float4 color2 = tex2D(textureSampler_Color2, IN.textureCoordinate_Color2);
  float4 color3 = tex2D(textureSampler_Color3, IN.textureCoordinate_Color3);
  float4 blend  = tex2D(textureSampler_Blend,  IN.textureCoordinate_Blend);

  float3 Normal	= normalize(IN.Normal);
  float NDotL   = dot(Normal, -LightDirection);
  float celVal  = clamp(NDotL, 0.0f, 1.0f);
  float2 celUV  = float2(celVal, celVal);
  float4 celCol = tex2D(textureSampler_Cel, celUV);

  OUT.pixelColor = ((color1 * blend.r) + (color2 * blend.g) + (color3 * blend.b)) * celCol.a;
}



float4 VertexShader_Outline(in gtVertex IN) : POSITION0
{
  return mul(IN.Position, matrix_WorldViewProj) + (mul(0.3f, mul(IN.Normal, matrix_WorldViewProj)));
}


float4 PixelShader_Outline() : COLOR0
{
  return float4(0.0f, 0.0f, 0.0f, 1.0f);
}




// Technique
technique simple
{
  pass p0
  {
    vertexshader = compile vs_2_0 vertex_shader();
    pixelshader  = compile ps_2_0 pixel_shader();
    CullMode = CCW;
  }
}
