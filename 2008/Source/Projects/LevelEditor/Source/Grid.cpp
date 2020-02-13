
#include "Grid.h"


Grid::Grid()
{
  m_Translation = 10.0f;            // Move 10 units at a time
  m_Rotation    = 360.0f / 16.0f;   // 16 segments of rotation
  m_Scale       = 0.1f;             // Scale by 10% at a time
  m_Enabled     = true;
}


Grid::~Grid()
{
}


void Grid::Snap(Vec3 *pPos, Vec3 *pRot, Vec3 *pScale)
{
  if (!m_Enabled)
  {
    return;
  }
  if (pPos)
  {
    RoundToNearset(*pPos, m_Translation);
  }
  if (pRot)
  {
    RoundToNearset(*pRot, m_Rotation);
  }
  if (pScale)
  {
    RoundToNearset(*pScale, m_Scale);
  }
}


void Grid::RoundToNearset(Vec3 &vec, float increment)
{
  for (uint i = 0; i < 3; i++)
  {
    float &value = vec[i];

    float remainder = fmodf(value, increment);
    if (remainder * 2.0f > increment)
    {
      // Round up
      value += (increment - remainder);
    }
    else
    {
      // Round down
      value -= remainder;
    }
  }
}


void Grid::Render()
{
  RenderState.Set(D3DRS_ZWRITEENABLE, FALSE);

  // Draw a mesh, scale it to fit

  RenderState.SetDefault(D3DRS_ZWRITEENABLE);
}


// -- EOF

