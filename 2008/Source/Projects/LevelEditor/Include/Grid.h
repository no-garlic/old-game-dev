
#ifndef __GRID_H_
#define __GRID_H_


#include "libEngine.h"
#include "libEditor.h"


class Grid : private Unique
{
public:
  Grid();
  virtual ~Grid();

  void SetEnabled(bool enabled)     { m_Enabled     = enabled;  }
  void SetTranslation(float units)  { m_Translation = units;    }
  void SetRotation(float degrees)   { m_Rotation    = degrees;  }
  void SetScale(float scale)        { m_Scale       = scale;    }

  void Snap(Vec3 *pPos, Vec3 *pRot, Vec3 *pScale);
  void Render();

private:
  void RoundToNearset(Vec3 &vec, float increment);

  float   m_Translation;
  float   m_Rotation;
  float   m_Scale;
  bool    m_Enabled;

};


#endif // __GRID_H_

// -- EOF

