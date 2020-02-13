
// Transforms
float4x4 m_world;
float4x4 m_view;
float4x4 m_projection;
float3 m_cameraPos;

// Simulation Parameters
float m_time;

// Water Parameters
float4 m_waterColor;
float4 m_specularColor;
float4 m_reflectiveColor;
float m_tileSizeX;
float m_tileSizeZ;

// Wave Parameters
float4 m_waveSpeeds;
float4 m_waveHeights;
float4 m_waveLengths;
float2 m_waveDir0;
float2 m_waveDir1;
float2 m_waveDir2;
float2 m_waveDir3;

// Texture Parameters
float m_bumpStrength;
float m_texStretch;
float m_texSpeed;

// Textures
Texture m_cubeMap;
Texture m_bumpMap;

// Environment Map Sampler
samplerCUBE CubeMapSampler = sampler_state 
{
  texture = <m_cubeMap>;
  magfilter = LINEAR; 
  minfilter = LINEAR; 
  mipfilter = LINEAR; 
  AddressU = mirror; 
  AddressV = mirror;
};

// Bump Map Sampler
sampler BumpMapSampler = sampler_state 
{
  texture = <m_bumpMap>;
  magfilter = LINEAR; 
  minfilter = LINEAR; 
  mipfilter = LINEAR; 
  AddressU = mirror; 
  AddressV = mirror;
};

// Vertex Shader Input
struct VSInput
{
  float4 Position : POSITION0;
  float2 TexCoord : TEXCOORD0;
};

// Vertex Shader Output
struct VSOutput
{
  float4 Position : POSITION;
  float2 TexCoord : TEXCOORD0;
  float3 Pos3D : TEXCOORD1;
  float3x3 TTW : TEXCOORD2;  
};

// Pixel Shader Output
struct PSOutput
{
  float4 Color : COLOR0;
};

// Vertex Shader
VSOutput VS(VSInput Input)
{
  VSOutput Output = (VSOutput)0;  
  
  float4 tPos = Input.Position;
  tPos.x += ((m_tileSizeX * -0.5f) + m_cameraPos.x);
  tPos.z += ((m_tileSizeZ * 0.5f) + m_cameraPos.z);
  
  float4 dotProducts;
  dotProducts.x = dot(m_waveDir0, tPos.xz);
  dotProducts.y = dot(m_waveDir1, tPos.xz);
  dotProducts.z = dot(m_waveDir2, tPos.xz);
  dotProducts.w = dot(m_waveDir3, tPos.xz);        
    
  float4 arguments = dotProducts / m_waveLengths + m_time * m_waveSpeeds;
  float4 heights = m_waveHeights * sin(arguments);
    
  float4 final3DPos = tPos;
  final3DPos.y += heights.x;
  final3DPos.y += heights.y;
  final3DPos.y += heights.z;
  final3DPos.y += heights.w;
  
  float4x4 preViewProjection = mul(m_view, m_projection);
  float4x4 preWorldViewProjection = mul(m_world, preViewProjection);
  Output.Position = mul(final3DPos, preWorldViewProjection);  
  
  float4 final3DPosW = mul(final3DPos, m_world);
  Output.Pos3D = final3DPosW;  
  
  float4 derivatives = m_waveHeights * cos(arguments) / m_waveLengths;
  float2 deviations = 0;
  deviations += derivatives.x * m_waveDir0;
  deviations += derivatives.y * m_waveDir1;
  deviations += derivatives.z * m_waveDir2;
  deviations += derivatives.w * m_waveDir3;  
  
  float3 Normal = float3(-deviations.x, 1, -deviations.y);  
  float3 Binormal = float3(1, deviations.x, 0);
  float3 Tangent = float3(0, deviations.y, 1);    
  
  float3x3 tangentToObject;
  tangentToObject[0] = normalize(Binormal);
  tangentToObject[1] = normalize(Tangent);
  tangentToObject[2] = normalize(Normal);    
  
  float3x3 tangentToWorld = mul(tangentToObject, m_world);
  Output.TTW = tangentToWorld;    
  
  Output.TexCoord = Input.TexCoord - ((m_cameraPos.xz * float2(-1,1)) / (m_texStretch * 30.0f)) + (m_time * m_texSpeed) / (200.0f) * float2(-1, 0);
  
  return Output;
}

// Pixel Shader
PSOutput PS(VSOutput PSIn) : COLOR0
{
  PSOutput Output = (PSOutput)0;          
    
  float3 bumpColor1 = tex2D(BumpMapSampler, m_texStretch * PSIn.TexCoord) - 0.5f;  
  float3 bumpColor2 = tex2D(BumpMapSampler, m_texStretch * 1.8 * PSIn.TexCoord.yx) - 0.5f;
  float3 bumpColor3 = tex2D(BumpMapSampler, m_texStretch * 3.1 * PSIn.TexCoord) - 0.5f;
  
  float3 normalT = bumpColor1 + bumpColor2 + bumpColor3;
  
  normalT.rg *= m_bumpStrength;
  normalT = normalize(normalT);
  float3 normalW = mul(normalT, PSIn.TTW);  
  
  float3 eyeVector = normalize(PSIn.Pos3D - m_cameraPos);  
  float3 reflection = reflect(eyeVector, normalW);    
  float4 reflectiveColor = texCUBE(CubeMapSampler, reflection);
  
  float fresnelTerm = dot(-eyeVector, normalW);  
  fresnelTerm = fresnelTerm / 2.0f + 0.5f;    
  
  float sunlight = reflectiveColor.r;
  sunlight += reflectiveColor.g;
  sunlight += reflectiveColor.b;
  sunlight /= 3.0f;
  float specularPower = pow(sunlight,30);  
  
  reflectiveColor *= m_reflectiveColor;
  float4 specular = m_specularColor * specularPower;
  
  Output.Color = m_waterColor * fresnelTerm + reflectiveColor * (1 - fresnelTerm) + specular;  
    
  return Output;
}

// Effect
technique OceanWater
{
  pass Pass0
  {  
    VertexShader = compile vs_2_0 VS();
    PixelShader  = compile ps_2_0 PS();
  }
}

