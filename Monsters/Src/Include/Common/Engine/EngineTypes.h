
#ifndef __ENGINE_TYPES_H_
#define __ENGINE_TYPES_H_


// --------------------------------------------------------------------------
// Fog definition
// --------------------------------------------------------------------------
struct Fog
{
  inline Fog();

  Color   color;
  float   start;
  float   end;
  float   density;
  bool    enabled;
}; // struct Fog


// --------------------------------------------------------------------------
// Directional light definition
// --------------------------------------------------------------------------
struct DirectionalLight
{
  inline DirectionalLight();

  Vec3    direction;
  Color   diffuse;
  Color   ambient;
  Color   specular;
  float   power;
  bool    enabled;
}; // struct DirectionalLight


// --------------------------------------------------------------------------
// Omni light definition
// --------------------------------------------------------------------------
struct OmniLight
{
  inline OmniLight();

  Vec3    position;
  Color   diffuse;
  Color   ambient;
  Color   specular;
  float   power;
  float   range;
  float   atten0;
  float   atten1;
  float   atten2;
  bool    enabled;
}; // struct OmniLight


// ----------------------------------------------------------------------------
// Name: Fog::Fog
// Desc: Constructor
// ----------------------------------------------------------------------------
inline Fog::Fog()
{
  color     = Color::White;
  start     = 10.0f;
  end       = 1000.0f;
  density   = 1.0f;
  enabled   = false;
} // Fog


// ----------------------------------------------------------------------------
// Name: DirectionalLight::DirectionalLight
// Desc: Constructor
// ----------------------------------------------------------------------------
inline DirectionalLight::DirectionalLight()
{
  D3DXVec3Set(&direction, 0.0f, -0.707f, 0.707f);
  diffuse     = Color(0.9f, 0.9f, 0.9f, 1.0f);
  ambient     = Color(0.05f, 0.05f, 0.05f, 1.0f);
  specular    = Color(0.6f, 0.6f, 0.6f, 1.0f);
  power       = 1.0f;
  enabled     = false;
} // DirectionalLight


// ----------------------------------------------------------------------------
// Name: OmniLight::OmniLight
// Desc: Constructor
// ----------------------------------------------------------------------------
inline OmniLight::OmniLight()
{
  D3DXVec3Set(&position, 0.0f, 0.0f, 0.0f);
  diffuse     = Color(0.9f, 0.9f, 0.9f, 1.0f);
  ambient     = Color(0.05f, 0.05f, 0.05f, 1.0f);
  specular    = Color(0.6f, 0.6f, 0.6f, 1.0f);
  power       = 1.0f;
  range       = 50.0f;
  atten0      = 0.1f;
  atten1      = 0.01f;
  atten2      = 0.001f;
  enabled     = false;
} // OmniLight


#endif // __ENGINE_TYPES_H_

// -- EOF
