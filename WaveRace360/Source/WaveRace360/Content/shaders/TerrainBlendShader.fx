
// Matrix
float4x4 matrix_WorldViewProj : WORLDVIEWPROJ;

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
  addressu = WRAP;
  addressv = WRAP;
};
sampler textureSampler_Color2 = sampler_state
{
  Texture = <texture_Color2>;
  magfilter = LINEAR;
  minfilter = LINEAR;
  mipfilter = LINEAR;
  addressu = WRAP;
  addressv = WRAP;
};
sampler textureSampler_Color3 = sampler_state
{
  Texture = <texture_Color3>;
  magfilter = LINEAR;
  minfilter = LINEAR;
  mipfilter = LINEAR;
  addressu = WRAP;
  addressv = WRAP;
};
sampler textureSampler_Blend = sampler_state
{
  Texture = <texture_Blend>;
  magfilter = LINEAR;
  minfilter = LINEAR;
  mipfilter = LINEAR;
  addressu = WRAP;
  addressv = WRAP;
};

// VS Input
struct gtVertex
{ 
  float4 Position : POSITION0;

};

// PS Input
struct gtPixelFormat
{
  float4 pixelPosition            : POSITION0;
  float2 textureCoordinate_Color1 : TEXCOORD0;
  float2 textureCoordinate_Color2 : TEXCOORD1;
  float2 textureCoordinate_Color3 : TEXCOORD2;
  float2 textureCoordinate_Blend  : TEXCOORD3;
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
}

// Pixel shader
void pixel_shader(in gtPixelFormat IN, out tScreenOutput OUT)
{
  float4 color1 = tex2D(textureSampler_Color1, IN.textureCoordinate_Color1);
  float4 color2 = tex2D(textureSampler_Color2, IN.textureCoordinate_Color2);
  float4 color3 = tex2D(textureSampler_Color3, IN.textureCoordinate_Color3);
  float4 blend  = tex2D(textureSampler_Blend,  IN.textureCoordinate_Blend);

  OUT.pixelColor = ((color1 * blend.r) + (color2 * blend.g) + (color3 * blend.b)) * blend.a;
  OUT.pixelColor.a = 1.0f;
}


// Technique
technique simple
{
  pass p0
  {
    sampler[0] = (textureSampler_Color1);	
    sampler[1] = (textureSampler_Color2);	
    sampler[2] = (textureSampler_Color3);	
    sampler[3] = (textureSampler_Blend);	

    vertexshader = compile vs_1_1 vertex_shader();
    pixelshader  = compile ps_1_1 pixel_shader();
  }
}
