
#ifndef __LIGHT_H_
#define __LIGHT_H_


#include "libRenderCore.h"


// ----------------------------------------------------------------------------
// Array of lights
// ----------------------------------------------------------------------------
typedef Array<D3DLIGHT *> LightArray;


// ----------------------------------------------------------------------------
// Directional Light
// ----------------------------------------------------------------------------
struct DirectionalLight : public D3DLIGHT
{
  // --------------------------------------------------------------------------
  // Constructor
  // --------------------------------------------------------------------------
  inline DirectionalLight(const Vec3 &direction = Vec3(0.0f, 1.0f, 0.0f),
                          const Color &ambient  = Color::Black, 
                          const Color &diffuse  = Color::White, 
                          const Color &specular = Color::White);
};


// ----------------------------------------------------------------------------
// Spot Light
// ----------------------------------------------------------------------------
struct SpotLight : public D3DLIGHT
{
  // --------------------------------------------------------------------------
  // Constructor
  // --------------------------------------------------------------------------
  inline SpotLight(const Vec3 &position  = Vec3(0.0f, 0.0f, 0.0f),
                   const Vec3 &direction = Vec3(0.0f, 1.0f, 0.0f),
                   float range           = FLT_MAX,
                   float falloff         = 1.0f,
                   float constantAtten   = 1.0f,
                   float linearAtten     = 1.0f,
                   float qudraticAtten   = 1.0f,
                   float innerCone       = PI / 2.0f,
                   float outerCone       = PI / 2.0f,
                   const Color &ambient  = Color::Black, 
                   const Color &diffuse  = Color::White, 
                   const Color &specular = Color::White);
};


// ----------------------------------------------------------------------------
// Point Light
// ----------------------------------------------------------------------------
struct PointLight : public D3DLIGHT
{
  // --------------------------------------------------------------------------
  // Constructor
  // --------------------------------------------------------------------------
  inline PointLight(const Vec3 &position  = Vec3(0.0f, 0.0f, 0.0f),
                    float range           = FLT_MAX,
                    float constantAtten   = 1.0f,
                    float linearAtten     = 1.0f,
                    float qudraticAtten   = 1.0f,
                    const Color &ambient  = Color::Black, 
                    const Color &diffuse  = Color::White, 
                    const Color &specular = Color::White);
};


// ----------------------------------------------------------------------------
// Directional Light Constructor
// ----------------------------------------------------------------------------
inline DirectionalLight::DirectionalLight(const Vec3 &direction, 
                                    const Color &ambient, 
                                    const Color &diffuse, 
                                    const Color &specular)
{
  ZeroMemory(this, sizeof(D3DLIGHT));

  Type      = D3DLIGHT_DIRECTIONAL;
  Direction = (D3DVECTOR) direction;
  Ambient   = ambient;
  Diffuse   = diffuse;
  Specular  = specular;
}


// ----------------------------------------------------------------------------
// Spot Light Constructor
// ----------------------------------------------------------------------------
inline SpotLight::SpotLight(const Vec3 &position,
                            const Vec3 &direction,
                            float range,
                            float falloff,
                            float constantAtten,
                            float linearAtten,
                            float qudraticAtten,
                            float innerCone,
                            float outerCone,
                            const Color &ambient,
                            const Color &diffuse,
                            const Color &specular)
{
  ZeroMemory(this, sizeof(D3DLIGHT));

  Type          = D3DLIGHT_SPOT;
  Position      = (D3DVECTOR) position;
  Direction     = (D3DVECTOR) direction;
  Range         = range;
  Falloff       = falloff;
  Attenuation0  = constantAtten;
  Attenuation1  = linearAtten;
  Attenuation2  = qudraticAtten;
  Theta         = innerCone;
  Phi           = outerCone;
  Ambient       = ambient;
  Diffuse       = diffuse;
  Specular      = specular;
}


// ----------------------------------------------------------------------------
// Point Light Constructor
// ----------------------------------------------------------------------------
inline PointLight::PointLight(const Vec3 &position,
                              float range,
                              float constantAtten,
                              float linearAtten,
                              float qudraticAtten,
                              const Color &ambient,
                              const Color &diffuse,
                              const Color &specular)
{
  ZeroMemory(this, sizeof(D3DLIGHT));

  Type          = D3DLIGHT_POINT;
  Position      = (D3DVECTOR) position;
  Attenuation0  = constantAtten;
  Attenuation1  = linearAtten;
  Attenuation2  = qudraticAtten;
  Ambient       = ambient;
  Diffuse       = diffuse;
  Specular      = specular;
}


#endif // __LIGHT_H_

// -- EOF

