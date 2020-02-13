
#ifndef __GAME_LIGHT_H_
#define __GAME_LIGHT_H_


#include "libEngine.h"
#include "GameObject.h"


class GameLight : public GameObject, public RefCounted
{
public:
  DECLARE_TYPE_INFO(GameObject);

  GameLight();
  virtual ~GameLight();

  D3DLIGHT *GetLight() { return &m_Light; }

  // --------------------------------------------------------------------------
  // Directional Light
  // --------------------------------------------------------------------------
  void SetDirectionalLight( const Vec3 &direction = Vec3(0.0f, 1.0f, 0.0f),
                            const Color &ambient  = Color::Black, 
                            const Color &diffuse  = Color::White, 
                            const Color &specular = Color::White)
  {
    m_Light = DirectionalLight(direction, ambient, diffuse, specular);
  }

  // --------------------------------------------------------------------------
  // Spot Light
  // --------------------------------------------------------------------------
  void SetSpotLight(        const Vec3 &position  = Vec3(0.0f, 0.0f, 0.0f),
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
                            const Color &specular = Color::White)
  {
    m_Light = SpotLight(position, direction, range, falloff, constantAtten, 
      linearAtten, qudraticAtten, innerCone, outerCone, ambient, diffuse, specular);
  }

  // --------------------------------------------------------------------------
  // Point Light
  // --------------------------------------------------------------------------
  void SetPointLight(       const Vec3 &position  = Vec3(0.0f, 0.0f, 0.0f),
                            float range           = FLT_MAX,
                            float constantAtten   = 1.0f,
                            float linearAtten     = 1.0f,
                            float qudraticAtten   = 1.0f,
                            const Color &ambient  = Color::Black, 
                            const Color &diffuse  = Color::White, 
                            const Color &specular = Color::White)
  {
    m_Light = PointLight(position, range, constantAtten, linearAtten, qudraticAtten, 
      ambient, diffuse, specular);
  }

protected:
  virtual void UpdateWorldTransform();

  D3DLIGHT m_Light;

};


#endif // __GAME_LIGHT_H_

// -- EOF

